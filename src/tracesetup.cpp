//
//  tracesetup.cpp
//  mydatabase
//
//  Created by Erik on 2019/11/1.
//  Copyright © 2019 Erik. All rights reserved.
//

#include "tracesetup.hpp"
tracesetup::tracesetup(){
    init();
}

void tracesetup::init(){
    ifstream read_trace(TRACEPATH,ios_base::in);
    string record; 
    int count_index=0;
    while (getline(read_trace,record)) {
        int RoW = stoi(record.substr(0,record.find(",")));
        int pid = stoi(record.substr(record.find(",")+1));
        trace[count_index].page_id=pid;
        if(RoW==1){
            trace[count_index].isWrite=1;
        }else{trace[count_index].isWrite=0;}
        count_index++;
    }
    read_trace.close();
}
