//
//  DSMgr.hpp
//  mydatabase
//
//  Created by Erik on 2019/11/1.
//  Copyright © 2019 Erik. All rights reserved.
//

#ifndef DSMgr_hpp
#define DSMgr_hpp
#include "tracesetup.hpp"
#include "BMgr.hpp"
class BMgr;

class DSMgr {
public:
    DSMgr();
    BMgr bmgr = BMgr();
    int OpenFile(string filename);
    int CloseFile();
    char * ReadPage(int page_id);
    int WritePage(int frame_id, bFrame *frm);
    int EnterWritePage(int frame_id, bFrame *frm);
    //int Seek(int offset, int pos);
    //FILE * GetFile();
    //void IncNumPages();
    //int GetNumPages();
    //void SetUse(int index, int use_bit);
    //int GetUse(int index);
private:
    void init();
    string path = "data.dbf";
    FILE *ReadFile;
    FILE *WriteFile;
    FILE *InitFile;
    char *frame;
    int numPages;
    //int pages[MAXPAGES];
};

#endif /* DSMgr_hpp */
