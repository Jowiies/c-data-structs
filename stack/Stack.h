#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Item {
    int _value;
    struct Item* _next;
} Item;

typedef struct Stack {
    Item* _topItem;
    size_t _size;
} Stack; 

Stack* newStack();
void stackPush(Stack*, int);
int stackPop(Stack*);
void itemsDelete(Item*);
void stackDelete(Stack*);

void stackPrint(Stack*);

#endif /* STACK_H */ 
