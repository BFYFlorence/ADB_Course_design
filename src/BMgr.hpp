//
//  BMgr.hpp
//  mydatabase
//
//  Created by Erik on 2019/11/1.
//  Copyright © 2019 Erik. All rights reserved.
//

#ifndef BMgr_hpp
#define BMgr_hpp
#include "tracesetup.hpp"
#include <stdio.h>


struct BCB {
    //BCB();
    int page_id;
    int frame_id;
    int count;
    //int dirty;
    //BCB * tohead;
    BCB * Totail = nullptr;
};

class BMgr
{
public:
    BMgr();
    // Interface functions
    void FixPage(int page_id);//           //执行插入操作
    void SelectAndDropVictim(int page_id);//
    int Hash(int page_id);//
    bool FindFrame(int page_id);//
    //void printbucket();
    void EnterFtop(int page_id);
    void LeaveFtop(int page_id);
    int Ftop(int page_id);                  //get frame_id through page_id
    int* ReturnFtop();
    //void FixNewPage();
    //int UnfixPage(int page_id);
    //int NumFreeFrames();
    //void RemoveBCB(BCB * ptr, int page_id);
    //void RemoveLRUEle(int frid);          该操作已在LRU.cpp里实现
    //void SetDirty(int frame_id);
    //void UnsetDirty(int frame_id);
    //void WriteDirtys();
    //void PrintFrame(int frame_id);
    
private:
    // Hash Table
    void init();
    int ftop[DEFBUFSIZE];
    BCB* ptof[DEFBUFSIZE];              
};

#endif /* BMgr_hpp */

