//
// Created by pabluxfirpux on 12/20/25.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "libs/String.h"

#define BYTESIZE "kb"
int memTotal, memFree, memUsed, memAvailable;

void list_process() {
    struct dirent *entry;
    DIR* dir = opendir("/proc");
    if (dir == NULL) {
        printf("Error opening /proc");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        char* name = entry->d_name;
        if (!isdigit(name[0])) {
            continue;
        }
        printf("%s\n", name);
    }
}


void load_MemData() {
    char* filename = "/proc/meminfo";
    char litlebuf1[256];
    char litlebuf2[256];
    int mem;
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Could not open %s\n", filename);
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
    printf("PROCESSES:\n");
    list_process();

    //TODO call /proc/PID/statm for each process, make struct wi
}