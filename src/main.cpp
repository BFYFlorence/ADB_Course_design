//
//  main.cpp
//  mydatabase
//
//  Created by Erik on 2019/11/1.
//  Copyright © 2019 Erik. All rights reserved.
//
//#include "BCB.hpp"
//#include "BMgr.hpp"
//#include "DSMgr.hpp"
#include "tracesetup.hpp"
#include "LRU.hpp"
#include "BMgr.hpp"
#include "DSMgr.hpp"
#include "time.h"


int main(int argc, const char * argv[]) {
    tracesetup records = tracesetup();
    BMgr bmgr = BMgr();
    DSMgr dsmgr = DSMgr();
    LRU lru = LRU();
    bFrame *frame = nullptr;
    int hit = 0;
    int io = 0;
    clock_t startTime = clock();
    for(int t=0;t<PAGEREF;t++){
        cout << "处理记录序号：" << t << endl;
        auto pageid = records.trace[t].page_id;
        auto isWrite = records.trace[t].isWrite;
        
        if(!lru.NodeExist(pageid)){         //如果LRU中pageid不存在
            dsmgr.ReadPage(pageid);
            io++;
            if(lru.InsertFeasible()){       //如果可插入（长度小于DEFBUFSIZE）
                Node *NewNode = new Node;
                NewNode->PageId = pageid;
                NewNode->isWri = records.trace[t].isWrite;
                lru.Insert(NewNode);
                bmgr.FixPage(pageid);
                bmgr.EnterFtop(pageid);
                if(isWrite){
                    NewNode->isDirty = true;
                }
            }else{                          //如果长度等于DEFBUFSIZE
                auto victim_pageid = lru.Head().totail->PageId;
                if(lru.Head().totail->isDirty){
                    dsmgr.WritePage(bmgr.Ftop(victim_pageid),frame);
                }
                bmgr.LeaveFtop(victim_pageid);
                bmgr.SelectAndDropVictim(victim_pageid);
                bmgr.FixPage(pageid);
                bmgr.EnterFtop(pageid);
                lru.Drop();
                Node *NewNode = new Node;
                NewNode->PageId = pageid;
                NewNode->isWri = records.trace[t].isWrite;
                lru.Insert(NewNode);
                if(isWrite){
                    NewNode->isDirty = true;
                }
            }
        }else{                              //如果LRU中已经存在
            hit++;
            lru.PickToTail(pageid);
            if(isWrite){
                lru.Tail().tohead->isDirty = true;
            }
        }
    }
    for(int j=0;j<DEFBUFSIZE;j++){
        if(bmgr.ReturnFtop()[j]!=-1){
            dsmgr.WritePage(j, frame);
        }
    }
    clock_t endTime = clock();
    cout << "算法运行时间：" << static_cast<double>(endTime - startTime)/CLOCKS_PER_SEC << "s" << endl;
    cout << "buffer size：" << DEFBUFSIZE << endl;
    cout << "hit数：" << hit << endl;
    cout << "hit rate："<< double(hit*100)/PAGEREF<<"%"<< endl;
    cout << "io数：" << io << endl;
}
