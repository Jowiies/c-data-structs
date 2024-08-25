#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* newStack() 
{
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    if (!stk) {
        fprintf(stderr, "Memory allocation error\n");
        exit(-1);
    }
    stk->_size = 0;
    stk->_topItem = NULL;
    return stk;
}

void stackPush(Stack* stk, int value)
{
    Item *ptr = (Item*)malloc(sizeof(Item));
    if (!ptr) {
        fprintf(stderr, "Memory allocation error\n");
        exit(-1);
    }
    ptr->_value = value;
    ptr->_next = stk->_topItem;
    stk->_topItem = ptr;
    stk->_size++;
}

int stackPop(Stack* stk)
{
    if (!stk) {
        fprintf(stderr, "Error: the stack was null\n");
        exit(-1);
    }
    if (stk->_size == 0) {
        fprintf(stderr, "Error: can't pop a void stack\n");
        exit(-1);
    }
    if (!stk->_topItem) {
        fprintf(stderr, "Error: the Item was null\n");
        exit(-1);
    }

    int value = stk->_topItem->_value;
    Item* deleteptr = stk->_topItem;
    stk->_topItem = stk->_topItem->_next;
    free(deleteptr);
    stk->_size--;
    return value;
}

void itemsDelete(Item* it)
{
    if (it == NULL)
        return;
    itemsDelete(it->_next);
    free((Item*)it);
}

void stackDelete(Stack* stk)
{
    itemsDelete(stk->_topItem);
    free(stk);
}

void stackPrint(Stack* stk) 
{
    Item* ptr = stk->_topItem;

    while (ptr != NULL) {
        printf("%d ", ptr->_value);
        ptr = ptr->_next;
    }

    printf("]\n size: %d\n",(int)stk->_size);
}
