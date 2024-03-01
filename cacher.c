#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "linkedList.h"
#include "myFuncs.h"

#define BUFF_SIZE 2048
char buffer[BUFF_SIZE];

int main(int argc, char **argv) {
    //Command line arguments (<policy> optional)
    //Format: ./cacher [-N size] <policy>
    if (argc < 3 || argc > 4) {
        warnx("wrong arguments: %s policy", argv[0]);
        fprintf(stderr, "usage: %s [-N size] <policy>\n", argv[0]);
        exit(1);
    }

    int opt;
    int size = 0;
    int policy = FIFO;
    while ((opt = getopt(argc, argv, "N:FLC")) != -1) {
        switch (opt) {
        case 'N':
            size = atoi(optarg);
            if (size <= 0) {
                write(STDERR_FILENO, "Error, invalid size\n", 20);
                exit(1);
            }
        //Set policy based on last policy flag
        case 'F': policy = FIFO; break;
        case 'L': policy = LRU; break;
        case 'C': policy = CLOCK; break;
        default: break; exit(1);
        }
    }

    int bytesRead = 0;
    int res = 0;
    do {
        res = read(STDIN_FILENO, buffer + bytesRead, BUFF_SIZE);
        if (res == -1) {
            write(STDERR_FILENO, "Error, invalid read\n", 20);
            exit(1);
        }

        bytesRead += res;
    } while (res != 0);

    //Initialize cache
    Cache *cache = (Cache *) malloc(sizeof(Cache));

    cache->list = create_list();
    cache->history_list = create_list();

    cache->clock_pointer = 0; //Only used in clock
    cache->max_size = size;
    cache->num_compulsory_misses = 0;
    cache->num_capacity_misses = 0;

    //Insert items into the cache
    char *token;
    token = strtok(buffer, "\n");
    while (token != NULL) {
        if (policy == FIFO) {
            insertFIFO(cache, token);
        } else if (policy == LRU) {
            insertLRU(cache, token);
        } else if (policy == CLOCK) {
            insertCLOCK(cache, token);
        }
        //printf("Added %s\n", token);
        //print_list(cache->list);
        //print_list(cache->history_list);
        //printf("\n");
        token = strtok(NULL, "\n");
    }

    printf("%i %i\n", cache->num_compulsory_misses, cache->num_capacity_misses);

    //Free dynamic memory
    destroy_list(&cache->list);
    cache->list = NULL;
    destroy_list(&cache->history_list);
    cache->history_list = NULL;
    free(cache);
    cache = NULL;

    return 0;
}
