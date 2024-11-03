#include "libsrc/dictionary.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static Dictionary dict = NULL;

void clearBuffer();
void searchFromFile(const char* filename);

int main(int argc, char **argv) 
{
    if (argc < 2) {
        fprintf(stderr, "Error: not enough parameters\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "Error: too many parameters\n");
        return 1;
    }
        
    FILE *words = fopen(argv[1], "r");
    if (words == NULL) {
        fprintf(stderr, "Error: couldn't open the file %s\n", argv[1]);
        return 1;
    }
    
    dict = newDictionary();
    char word[50] = {0};
    char description[500] = {0};
    
    while (fgets(word, sizeof(word), words) != NULL){
        
        word[strcspn(word,"\n")] = 0;

        if(fgets(description, sizeof(description), words) == NULL) {
            fprintf(stderr, "Error reading the description: Aborting");
            return 1;
        }
        
        description[strcspn(description, "\n")] = 0;
        dictionaryInsert(dict, word, description);
    }
    
    fclose(words);
    int opt;
    printf("1. Insert\n2. Delete\n3. Search\n");
    while (1) {
        printf("Input: ");
        scanf("%d",&opt);

        switch (opt) {
            case 1: {
                scanf("%49s", word);
               
                clearBuffer();
              
                fgets(description, sizeof(description) -1 , stdin);
                description[strcspn(description, "\n")] = 0;
                
                dictionaryInsert(dict, word, description);
                break;
            }
            case 2: {
                scanf("%49s", word);
                dictionaryRemoveWord(dict, word);
                break;
            }
            case 3: {
                scanf("%49s", word);
                const char* desc = dictionarySearch(dict, word); 
                if (desc == NULL) {
                    printf("The word %s isn't in the dictionary\n", word);
                }
                else {
                    printf("The description of the word %s is:\n%s\n",word, desc);
                }
                break;
            }
            default: {
                opt = -1;
                break;
            }
        }
        if (opt == -1)
            break;
        
    }

    freeDictionary(dict);

    return 0;
}

void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void searchFromFile(const char* filename)
{
    char word[50] = {0};
    FILE *search = fopen(filename, "r");
    
    while (fgets(word, sizeof(word), search) != NULL){
       
        word[strcspn(word,"\n")] = 0;
        const char* desc = dictionarySearch(dict, word);
        
        if (desc != NULL)
            printf("The description of the word %s is:\n%s\n", word, desc);
        else
            printf("Word %s not found\n", word);
    }

    fclose(search);
}
