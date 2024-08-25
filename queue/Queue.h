#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct Item {
    int _val;
    struct Item *_next;
} Item;

typedef struct Queue {
    size_t _size;
    Item *_first;
    Item *_last;
} Queue;

Queue* newQueue();
void queueInsert(Queue*, int);
int queuePop(Queue*);
void freeQueue(Queue*);

#endif /* QUEUE_H */
