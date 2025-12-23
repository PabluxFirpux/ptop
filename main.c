//
// Created by pabluxfirpux on 12/20/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "libs/String.h"
#include "screen.h"
#include "proces.h"

#define BYTESIZE "kb"
int memTotal, memFree, memUsed, memAvailable;

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
    fclose(f);
}

void screen() {
    initscr();
    load_MemData();
    printw("Memory total: %d %s\n", memTotal, BYTESIZE);
    printw("Memory Free: %d %s\n", memFree, BYTESIZE);
    printw("Memory Available: %d %s\n", memAvailable, BYTESIZE);
    printw("Memory Used: %d %s\n", memUsed, BYTESIZE);
    refresh();			/* Print it on to the real screen */
    getch();/* Wait for user input */
    endwin();
}

void print_procInfo(Proces *pproces) {
    if (!pproces) {
        return;
    }
    printf("Process ID: %d\n", pproces->id);
    printf("Name: %s\n", pproces->name);
    printf("Mem: %d %d %d\n", pproces->sizeInKB, pproces->resSizeInKB, pproces->shareSizeInKB);
}

int main(int argc, char *argv[]) {
    //test_Colors();
    if (argc != 2) {
        printf("Usage: ./ptop <process id>\n");
        return 1;
    }
    int id = atoi(argv[1]);


    ProcList* pproces_list = PROCES_list_process();
    for (int i = 0; i < pproces_list->length; i++) {
        if (pproces_list->procesList[i] == NULL || pproces_list->procesList[i] == 0) {
            continue;
        }
        print_procInfo(pproces_list->procesList[i]);
    }
    free(pproces_list);
    return 0;

    load_MemData();
    printf("Memory total: %d %s\n", memTotal, BYTESIZE);
    printf("Memory Free: %d %s\n", memFree, BYTESIZE);
    printf("Memory Available: %d %s\n", memAvailable, BYTESIZE);
    printf("Memory Used: %d %s\n", memUsed, BYTESIZE);


    return 0;
    //TODO: call /proc/PID/statm for each process, make struct with info
}