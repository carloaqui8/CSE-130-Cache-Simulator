#pragma once

#include <stdio.h> //JUST FOR TESTING DELETE LATER
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    int r_bit;
    struct Node *next;
} Node;

typedef struct ListObj {
    Node *head;
    int length;
} ListObj;

//Constructor and Destructor
ListObj *create_list();
void destroy_list(ListObj **);

//Methods
void append_list(ListObj *, char *);
char *remove_front(ListObj *);
Node *find_list(ListObj *, char *); //Based on data
void move_to_back(ListObj *, Node *);
Node *get_item(ListObj *, int); //Based on index
Node *overwrite_item(ListObj *, int, char *);

//JUST FOR TESTING DELETE LATER
void print_list(ListObj *L);
