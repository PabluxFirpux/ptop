//
// Created by pabluxfirpux on 12/22/25.
//

#include "proces.h"
#include <stdio.h>
#include <stdlib.h>

#define KILOBYTE 1024
//TODO: FIND WAY TO GET PAGESIZE FROM OS
#define PAGESIZE 4096


int turnPageIntoKB(int sizeInPages, int pagesizeInBytes) {
    long long sizeINBytes = ((long long) sizeInPages) * ((long long) pagesizeInBytes);
    long long sizeInKB = sizeINBytes /(long long) KILOBYTE;
    return sizeInKB;
}
// Devuelve los tres valores que usaremos (program size) (resident set size) (shared pages)
void getProcessMemUsage(int* store,int id) {
    const char* filenamePart1 = "/proc/";
    const char* filenamePart2 = "/statm";
    char pid[30];
    char filename[256];
    int progSizeInPages, resSizeInPages, shareSizeInPages;

    sprintf(pid, "%d", id);
    sprintf(filename, "%s%s%s", filenamePart1, pid, filenamePart2);
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Could not open %s\n", filename);
        exit(1);
    }

    // Scan Total mem using
    fscanf(f, "%d %d %d", &progSizeInPages, &resSizeInPages, &shareSizeInPages);
    fclose(f);
    store[0] = progSizeInPages;
    store[1] = resSizeInPages;
    store[2] = shareSizeInPages;
}

Proces* PROCES_getProces(int id) {
    // Values of /proc/PID/statm are 7: 1(total program size) 2(resident set size) 3(resident shared pages)
    // 4(text(code)) 5(lib (library)) ---- Solo usar los primeros 3 que son los que salen en el "top"

    int* memInPages = malloc(3*sizeof(int));
    getProcessMemUsage(memInPages, id);
    int progSizeInKB, resSizeInKB, shareSizeInKB;
    progSizeInKB = turnPageIntoKB(memInPages[0], PAGESIZE);
    resSizeInKB = turnPageIntoKB(memInPages[1], PAGESIZE);
    shareSizeInKB = turnPageIntoKB(memInPages[2], PAGESIZE);

    free(memInPages);

    Proces* proces = malloc(sizeof(Proces));
    proces->id = id;
    proces->sizeInKB = progSizeInKB;
    proces->resSizeInKB = resSizeInKB;
    proces->shareSizeInKB = shareSizeInKB;
    return proces;
}