#include "linkedList.h"

ListObj *create_list() {
    ListObj *L = (ListObj *) malloc(sizeof(ListObj));

    L->head = NULL; //Set attributes
    L->length = 0;

    return L;
}

void destroy_list(ListObj **L) {
    Node *curr = (*L)->head; //2 used for list deletion
    Node *ptr2 = NULL;
    (*L)->head = NULL;
    (*L)->length = 0;

    if (*L == NULL) { //Passed in NULL
        return;
    } else { //Cycle through nodes and free them
        while (curr != NULL) {
            ptr2 = curr->next;
            //free(curr->data);
            //curr->data = NULL;
            free(curr);
            curr = NULL;
            curr = ptr2;
        }
    }

    free(*L); //Free the list itself
    *L = NULL; //and set to null
}

void append_list(ListObj *L, char *data) {
    Node *N = (Node *) malloc(sizeof(Node)); //Create the new node
    N->data = data;
    N->r_bit = 0;
    N->next = NULL;

    if (L->length == 0) { //List is empty
        L->head = N;
    } else { //Go to the end and insert new node
        Node *curr = L->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = N;
    }
    L->length++;
}

char *remove_front(ListObj *L) {
    Node *curr = L->head;
    void *returnData = curr->data;

    L->head = L->head->next;
    L->length--;

    free(curr);
    curr = NULL;

    return returnData;
}

Node *find_list(ListObj *L, char *key) { //Based on data
    Node *curr = L->head;
    if (L->length == 0) { //List is empty
        return NULL;
    }
    while (curr != NULL) { //Cycle through the list to try and find data
        if (strcmp(curr->data, key) == 0) { //If found, return the the data
            return curr;
        } else {
            curr = curr->next;
        }
    } // Not found -> return NULL
    return NULL;
}

void move_to_back(ListObj *L, Node *N) {
    Node *prev = NULL; //Follows curr
    Node *curr = L->head;
    Node *last = L->head; //Last element in L
    while (strcmp(curr->data, N->data) != 0) { //Get curr to where N is found
        prev = curr;
        curr = curr->next;

        if (curr == NULL) {
            fprintf(stderr, "Error, element couldn't be moved to the back\n");
            exit(1);
        }
    }
    while (last->next != NULL) { //Get last to the last element
        last = last->next;
    }

    if (curr == last) { //Case 1: curr == last -> change nothing
        return;
    }
    if (strcmp(curr->data, L->head->data) == 0) { //Case 2: curr is the head -> update head
        L->head = curr->next;
    }
    last->next = curr; //Case 3: General case -> move to the back
    if (prev != NULL) {
        prev->next = curr->next;
    }
    curr->next = NULL;
}

Node *get_item(ListObj *L, int index) { //Based on index
    if (index < 0 || index >= L->length) {
        fprintf(stderr, "Error, index out of range\n");
        exit(1);
    }

    Node *curr = L->head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    return curr;
}

Node *overwrite_item(ListObj *L, int index, char *data) {
    if (index < 0 || index >= L->length) {
        fprintf(stderr, "Error, index out of range\n");
        exit(1);
    }

    Node *N = (Node *) malloc(sizeof(Node)); //Create the new node
    N->data = data;
    N->r_bit = 0;
    N->next = NULL;

    Node *curr = L->head;
    Node *prev = NULL;
    for (int i = 0; i < index; i++) { //Move curr and prev where they're supposed to be
        prev = curr;
        curr = curr->next;
    }

    if (strcmp(curr->data, L->head->data) == 0) { //Case 1: curr is the head -> update head
        L->head = N;
        N->next = curr->next;
    }
    if (prev != NULL) { //Case 2: General case
        prev->next = N;
        N->next = curr->next;
    }

    return curr;
}

//JUST FOR TESTING DELETE LATER
void print_list(ListObj *L) {
    Node *curr = L->head;
    if (L->length == 0) {
        printf("Empty list\n");
        return;
    }
    while (curr != NULL) {
        printf("%s,%i\t", curr->data, curr->r_bit);
        curr = curr->next;
    }
    printf("\n");
}
