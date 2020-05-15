//
//  DSMgr.cpp
//  mydatabase
//
//  Created by Erik on 2019/11/1.
//  Copyright © 2019 Erik. All rights reserved.
//

#include "DSMgr.hpp"
DSMgr::DSMgr(){
    init();
}

void DSMgr::init(){
    frame = new char[FRAMESIZE];  //开辟一个数组
    if(OpenFile(path)){
        char *content = new char [PAGENUM*PAGESIZE];
        memset(content, 0, sizeof(*content));
        fwrite(content,sizeof(char),PAGENUM*PAGESIZE,InitFile);
    }else{cout << "We have a problem on opening file" << endl;}
}

int DSMgr::OpenFile(string filename){
    InitFile = fopen(filename.c_str(), "w");
    ReadFile = fopen(filename.c_str(), "r");            //filename为字符串，需要将其转换成char数组
    WriteFile = fopen(filename.c_str(), "r+");
    return 1;
}

int DSMgr::CloseFile(){
    fclose(ReadFile);
    fclose(WriteFile);
    fclose(InitFile);
    return 1;
}

int DSMgr::WritePage(int frame_id, bFrame *frm){
    int page_id = bmgr.ReturnFtop()[frame_id];
    fseek(InitFile, sizeof(char)*PAGESIZE*(page_id-1), SEEK_SET);
    fwrite(frm->field, sizeof(char), PAGESIZE, WriteFile);
    return 1;
}

int DSMgr::EnterWritePage(int page_id, bFrame *frm){
    fseek(InitFile, sizeof(char)*PAGESIZE*(page_id-1), SEEK_SET);
    fwrite(frm->field, sizeof(char), PAGESIZE, WriteFile);
    return 1;
}


char * DSMgr::ReadPage(int page_id){
    fseek(InitFile, sizeof(char)*PAGESIZE*(page_id-1), SEEK_SET);
    fread(frame,sizeof(char),PAGESIZE,ReadFile);
    return frame;
}
