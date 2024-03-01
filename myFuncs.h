#pragma once

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "linkedList.h"

typedef struct Cache {
    //Policy policy;
    ListObj *list;
    ListObj *history_list;
    int clock_pointer; //Only used in clock
    int max_size;

    int num_compulsory_misses;
    int num_capacity_misses;
} Cache;

enum Policy {
    FIFO,
    LRU,
    CLOCK,
};

int insertFIFO(Cache *cache, char *elem);
int insertLRU(Cache *cache, char *elem);
int insertCLOCK(Cache *cache, char *elem);

void printHit();
void printMiss();
