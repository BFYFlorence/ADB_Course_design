//
//  LRU.cpp
//  mydatabase
//
//  Created by Erik on 2019/11/2.
//  Copyright © 2019 Erik. All rights reserved.
//

#include "LRU.hpp"
#include "tracesetup.hpp"
LRU::LRU(){
    init();
}


void LRU::init(){
    head.tohead = nullptr;
    head.totail = &tail;
    tail.totail = nullptr;
    tail.tohead = &head;
    tail.PageId = -1;
    head.PageId = -2;
    LRUnum = 0;
}

bool LRU::InsertFeasible(){
    if (LRUnum<DEFBUFSIZE){return true;}else{return false;}
}

void LRU::Insert(Node *newnode){
    newnode ->totail = &tail;
    newnode ->tohead = tail.tohead;
    tail.tohead ->totail = newnode;
    tail.tohead = newnode;
    LRUnum++;
}

void LRU::Drop(){
    head.totail->totail->tohead = &head;
    head.totail = head.totail->totail;
}

bool LRU::NodeExist(int pageid){
    Node * current = tail.tohead;
    while(current ->PageId!=-2){
        if(current ->PageId==pageid){
            return true;
        }else{
            current = current ->tohead;
        }
    }
    return false;
}

Node LRU::Head(){
    return head;
}


Node LRU::Tail(){
    return tail;
}

void LRU::PickToTail(int pageid){
    Node * current = tail.tohead;
    while(current->PageId!=pageid){
        current = current ->tohead;
    }
    current ->totail ->tohead = current ->tohead;
    current ->tohead ->totail = current ->totail;
    current ->totail = &tail;
    current ->tohead = tail.tohead;
    tail.tohead->totail = current;
    tail.tohead = current;
}

