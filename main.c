//
// Created by pabluxfirpux on 12/20/25.
//

#include <stdio.h>
#include <stdlib.h>
#include "libs/String.h"

#define BYTESIZE "kb"
int memTotal, memFree, memUsed, memAvailable;


void load_MemData() {
    char litlebuf1[256];
    char litlebuf2[256];
    int mem;
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) {
        printf("Could not open /proc/meminfo\n");
        exit(1);
    }
    // Scanning vs reading: fscanf formats input. fgets just gets the line

    // Scan Total mem using
    fscanf(f, "%s %d %s", litlebuf1, &mem, litlebuf2);
    memTotal = mem;

    //Scan Free mem
    fscanf(f, "%s %d %s", litlebuf1, &mem, litlebuf2);
    memFree = mem;

    //Scan Available mem
    fscanf(f, "%s %d %s", litlebuf1, &mem, litlebuf2);
    memAvailable = mem;

    //Calculate memUsed
    memUsed = memTotal-memAvailable;
}

int main(int argc, char *argv[]) {
    load_MemData();
    printf("Memory total: %d %s\n", memTotal, BYTESIZE);
    printf("Memory Free: %d %s\n", memFree, BYTESIZE);
    printf("Memory Available: %d %s\n", memAvailable, BYTESIZE);
    printf("Memory Used: %d %s\n", memUsed, BYTESIZE);
}