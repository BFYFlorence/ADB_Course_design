//
//  LRU.hpp
//  mydatabase
//
//  Created by Erik on 2019/11/2.
//  Copyright © 2019 Erik. All rights reserved.
//

#ifndef LRU_hpp
#define LRU_hpp
#include <iostream>
using namespace std;
struct Node{
    Node * tohead;
    Node * totail;
    int PageId;
    bool isWri;
    bool isDirty = false;
};

class LRU{
public:
    LRU();
    bool InsertFeasible();
    void Insert(Node *newnode);
    void Drop();
    bool NodeExist(int pageid);
    void PickToTail(int pageid);
    //void printLRU();
    Node Head();
    Node Tail();
private:
    void init();
    int LRUnum;
    Node head;    //这个地方不能只初始化指针，因为需要一个头尾部的实例结点
    Node tail;
};
#include <stdio.h>

#endif /* LRU_hpp */
