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
} Proces;

Proces* PROCES_getProces(int id);

#endif //PTOP_PROCES_H