#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue* newQueue()
{
    Queue *qu = (Queue*)malloc(sizeof(Queue));
    if (!qu) {
        fprintf(stderr, "Error at memory allocation!");
        exit(1);
    }
    qu->_first = NULL;
    qu->_last = NULL;
    qu->_size = 0;
    return qu;
}


void queueInsert(Queue* qu, int value) 
{
    Item* newitem = (Item*)malloc(sizeof(Item));
    if (!newitem) {
        fprintf(stderr, "Error at memory allocation!");
        exit(1);
    }
    newitem->_val = value;
    newitem->_next = NULL;
    if (qu->_first == NULL) {
        qu->_first = qu->_last = newitem;
    }
    else {
        qu->_last->_next = newitem;
        qu->_last = qu->_last->_next;
    }
    qu->_size++;
}


int queuePop(Queue *qu)
{
    if (qu->_size == 0) {
        fprintf(stderr, "Error: trying to pop an empty queue");
        exit(1);
    }
    int value = qu->_first->_val;
    Item* deleteptr = qu->_first;
    if (qu->_first == qu->_last) {
        qu->_first = qu->_last = NULL;
    }
    else {
        qu->_first = qu->_first->_next;
    }
    qu->_size--;
    free(deleteptr);
    return value;
}


void freeQueue(Queue *qu)
{
    Item *ptr = NULL;
    while (qu->_first != NULL) {
        ptr = qu->_first;
        qu->_first = qu->_first->_next;
        free(ptr);
    }
    qu->_size = 0;
    free(qu);
}



