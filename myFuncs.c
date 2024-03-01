#include "myFuncs.h"

int insertFIFO(Cache *cache, char *elem) {
    //Check for invalid arguments
    if (cache == NULL || elem == NULL) {
        write(STDERR_FILENO, "Error, invalid insert\n", 22);
        exit(1);
    }

    //Check if list contains the element
    if (find_list(cache->list, elem) != NULL) {
        printHit();
        return 1;
    }

    //Check if list if full
    char *data = NULL;
    if (cache->list->length == cache->max_size) {
        data = remove_front(cache->list);
    }

    //Check if history_list contains the element
    //Choose miss accordingly
    if (find_list(cache->history_list, elem) != NULL) {
        cache->num_capacity_misses++;
    } else {
        cache->num_compulsory_misses++;
    }
    printMiss();

    //Add removed element to history_list
    if (data != NULL) {
        append_list(cache->history_list, data);
    }

    //Add element to the list
    append_list(cache->list, elem);

    return 0;
}

int insertLRU(Cache *cache, char *elem) {
    //Check for invalid arguments
    if (cache == NULL || elem == NULL) {
        write(STDERR_FILENO, "Error, invalid insert\n", 22);
        exit(1);
    }

    //Check if list contains the element
    if (find_list(cache->list, elem) != NULL) {
        printHit();
        move_to_back(cache->list, find_list(cache->list, elem));

        return 1;
    }

    //Check if list if full
    if (cache->list->length == cache->max_size) {
        char *data;
        data = remove_front(cache->list);

        //Add removed element to history_list
        append_list(cache->history_list, data);
    }

    //Check if history_list contains the element
    //Choose miss accordingly
    if (find_list(cache->history_list, elem) != NULL) {
        cache->num_capacity_misses++;
    } else {
        cache->num_compulsory_misses++;
    }
    printMiss();

    //Add element to the list
    append_list(cache->list, elem);

    return 0;
}

int insertCLOCK(Cache *cache, char *elem) {
    //Check for invalid arguments
    if (cache == NULL || elem == NULL) {
        write(STDERR_FILENO, "Error, invalid insert\n", 22);
        exit(1);
    }

    //Check if list contains the element
    if (find_list(cache->list, elem) != NULL) {
        Node *item = find_list(cache->list, elem);
        item->r_bit = 1;
        printHit();

        return 1;
    }

    //Check if list if full
    if (cache->list->length == cache->max_size) {
        Node *item = get_item(cache->list, cache->clock_pointer);

        while (item->r_bit == 1) {
            item->r_bit = 0;
            cache->clock_pointer = (cache->clock_pointer + 1) % cache->max_size;
            item = get_item(cache->list, cache->clock_pointer);
        }

        item = overwrite_item(cache->list, cache->clock_pointer, elem);
        cache->clock_pointer = (cache->clock_pointer + 1) % cache->max_size;

        //handle adding to history_list
        append_list(cache->history_list, item->data);
        free(item);
        item = NULL;
    }

    //Check if history_list contains the element
    //Choose miss accordingly
    if (find_list(cache->history_list, elem) != NULL) {
        cache->num_capacity_misses++;
    } else {
        cache->num_compulsory_misses++;
    }
    printMiss();

    //Add element to the list if you didn't run the above code
    if (cache->list->length != cache->max_size) {
        append_list(cache->list, elem);
    }

    return 0;
}

void printHit() {
    fprintf(stdout, "HIT\n");
}
void printMiss() {
    fprintf(stdout, "MISS\n");
}
