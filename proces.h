//
// Created by pabluxfirpux on 12/22/25.
//

#ifndef PTOP_PROCES_H
#define PTOP_PROCES_H

typedef struct {
    int id;
    int sizeInKB;
    int resSizeInKB;
    int shareSizeInKB;
    char name[256];
} Proces;

typedef struct {
    Proces** procesList;
    int length;
} ProcList;

ProcList* PROCES_list_process();
Proces* PROCES_getProces(int id);

#endif //PTOP_PROCES_H