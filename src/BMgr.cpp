//
//  BMgr.cpp
//  mydatabase
//
//  Created by Erik on 2019/11/1.
//  Copyright © 2019 Erik. All rights reserved.
//

#include "BMgr.hpp"
BMgr::BMgr(){
    init();
}

void BMgr::init(){
    for(int i=0;i<DEFBUFSIZE;i++){
        BCB * FirstBCB = new BCB;
        ptof[i] = FirstBCB;
        FirstBCB->count = 0;
        FirstBCB->page_id = -2;
        FirstBCB->Totail = nullptr;
        ftop[i] = -1;
    }
}

int BMgr::Hash(int page_id){
    return page_id % DEFBUFSIZE;
}

void BMgr::FixPage(int page_id){                  //根据pageid插入进buffer,不判断计数器
    int frameid = Hash(page_id);
    (ptof[frameid]->count)++;
    BCB * current = ptof[frameid];
    while (current->Totail!=nullptr) {
        current = current->Totail;
    }
    BCB * NewBCB = new BCB;
    NewBCB->page_id = page_id;
    NewBCB->Totail = nullptr;
    current->Totail = NewBCB;
}

bool BMgr::FindFrame(int page_id){               //查找pageid是否存在于buffer中
    int frameid = Hash(page_id);
    BCB * current = ptof[frameid];
    while (current->Totail!=nullptr && current->page_id!=page_id) {
        current = current->Totail;
    }
    if(current->page_id==page_id){
        return true;
    }else{
        return false;
    }
}

void BMgr::SelectAndDropVictim(int page_id){
    int frameid = Hash(page_id);
    BCB * current = ptof[frameid];
    (ptof[frameid]->count)--;
    while (current->Totail->page_id!=page_id) {
        current = current->Totail;
    }
    if(current->Totail->Totail==nullptr){
        current->Totail = nullptr;
    }else{
        current->Totail = current->Totail->Totail;
    }
}

void BMgr::EnterFtop(int page_id){
    for(int i=0;i<DEFBUFSIZE;i++){
        if(ftop[i]!=-1){
            ftop[i]=page_id;
        }
    }
}

void BMgr::LeaveFtop(int page_id){
    for(int i=0;i<DEFBUFSIZE;i++){
        if(ftop[i]==page_id){
            ftop[i]=-1;
        }
    }
}

int BMgr::Ftop(int page_id){
    int i =0;
    while(ftop[i]!=page_id){
        i++;
    }
    return i;
}

int* BMgr::ReturnFtop(){
    return ftop;
}
