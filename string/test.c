#include "String.h"
#include <stdio.h>

#define MAX_CHARACTERS 50

int main(int argc, char **argv)
{
    String *str;
    if (argc == 1) {
        str = newString("Hello, World!");
    }
    else {
        str = newString(argv[1]);
    }

    printf("String = %s\n Size = %d\n", str->_s, (int)str->_length);
    
    str->addStr(str, "Bomboclat");  
    printf("String = %s\n Size = %d\n", str->_s, (int)str->_length);

    str->sinkStr(str, 3);
    printf("String = %s\n Size = %d\n", str->_s, (int)str->_length);
    
    str->deleteStr(str);
}
