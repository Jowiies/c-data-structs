#include "Stack.h"
#include <stdio.h>
#include <string.h>

int main() 
{
    char str[50];
    Stack* stk = newStack();
    while (scanf("%s", str) == 1) {
        if (strcmp(str,"pop") == 0){

        }
        else if (strcmp(str,"push") == 0){

        }
    }
    stackPrint(stk);
    stackDelete(stk);
    return 0;
}
