//
// Created by pabluxfirpux on 12/22/25.
//
#include "proces.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define KILOBYTE 1024
//TODO: FIND WAY TO GET PAGESIZE FROM OS
#define PAGESIZE 4096

int number_of_proceses() {
    struct dirent *entry;
    DIR* dir = opendir("/proc");
    if (dir == NULL) {
        printf("Error opening /proc");
        exit(1);
    }

    int proces_count = 0;
    while ((entry = readdir(dir)) != NULL) {
        char* name = entry->d_name;
        if (!isdigit(name[0])) {
            continue;
        }
        proces_count ++;
    }
    closedir(dir);
    return proces_count;
}

void PROCES_list_process(Proces** proces_list_to_fill) {
    struct dirent *entry;
    DIR* dir = opendir("/proc");
    if (dir == NULL) {
        printf("Error opening /proc");
        exit(1);
    }

    int proces_count = number_of_proceses();
    proces_list_to_fill = malloc(proces_count * sizeof(Proces));

    int i = -1;
    while ((entry = readdir(dir)) != NULL) {
        char* name = entry->d_name;
        if (!isdigit(name[0])) {
            continue;
        }
        i++;
        int id = atoi(name);
        proces_list_to_fill[i] = PROCES_getProces(id);
    }
}

int turnPageIntoKB(int sizeInPages, int pagesizeInBytes) {
    long long sizeINBytes = ((long long) sizeInPages) * ((long long) pagesizeInBytes);
    long long sizeInKB = sizeINBytes /(long long) KILOBYTE;
    return sizeInKB;
}

void loadNameCommandAndUptime(Proces* proces) {
    const char filename[256];
    sprintf(filename,"/proc/%d/stat", proces->id);
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Could not open %s\n", filename);
        exit(1);
    }

    //Total of 52 values. We want 2(name) and 22(startime)
    // Everything can be parsed as %llu except 2 and 3 that are %s and %c
    unsigned long long value = 0;
    unsigned long long value2 = 0;
    char processName[256];
    char discard;

    //Escaneamos los primeros 4 para poder iterar despues
    fscanf(f, "%llu %s %c %llu", &value, &processName, &discard, &value2);
    for (int i = 4; i<44; i++) {
        fscanf(f, "%llu", &value);
    }
    //printf("Startime: %llu", value/ sysconf(_SC_CLK_TCK));
    strcpy(proces->name, processName);
    fclose(f);
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

    //Now get CPU% y MEM% y TIME+COMMAND

    Proces* proces = malloc(sizeof(Proces));
    proces->id = id;
    proces->sizeInKB = progSizeInKB;
    proces->resSizeInKB = resSizeInKB;
    proces->shareSizeInKB = shareSizeInKB;
    loadNameCommandAndUptime(proces);
    return proces;
}