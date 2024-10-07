#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

static Dictionary dict = NULL;

int isAlphabethic(const char* token);

int main(int argc, char **argv) 
{
    if (argc < 2) {
        fprintf(stderr, "Error: not enough parameters\n");
        return 1;
    }

    if (argc > 3) {
        fprintf(stderr, "Error: too many parameters\n");
        return 1;
    }
    
    FILE *words = fopen(argv[1], "r");
    if (words == NULL) {
        fprintf(stderr, "Error: couldn't open the file %s\n", argv[1]);
        return 1;
    }
    
    dict = newDictionary();
    char line[MAX_LINE_LENGTH] = {0};
    char *word = NULL;
    
    while (fgets(line, sizeof(line), words) != NULL){
        
        word = strtok(line, " ,.-!?\n\r");
        
        while (word != NULL) {

            if (isAlphabethic(word))
                dictionaryInsert(dict, word); 
            
            word = strtok(NULL, " ,.-!?\n\r");
        }
    }

    fclose(words);

    printDictionary(dict);

    freeDictionary(dict);

    return 0;
}


int isAlphabethic(const char* token)
{
    for (size_t i = 0; token[i] != '\0'; ++i) {
        if (!isalpha(token[i])) {
            return 0;
        }
    }
    return 1;
}
