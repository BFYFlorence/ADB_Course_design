//
//  tracesetup.hpp
//  mydatabase
//
//  Created by Erik on 2019/11/1.
//  Copyright © 2019 Erik. All rights reserved.
//

#ifndef tracesetup_hpp
#define tracesetup_hpp

#include <iostream>
#include <fstream>
#include <string>
#define FRAMESIZE 4096
#define PAGESIZE 4096
#define DEFBUFSIZE 2048
#define PAGENUM 50000
#define PAGEREF 500000
using namespace std;

struct bFrame {
    char field[FRAMESIZE];
};

struct singlerecord{
    int page_id;
    bool isWrite;
};

class tracesetup{
public:
    tracesetup();
    singlerecord trace[PAGEREF];
private:
    void init();
    string TRACEPATH="data-5w-50w-zipf.txt";
};
#endif /* tracesetup_hpp */
