#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define ENDCHAR '#'

typedef struct Node {
    char _key;
    struct Node *_child;
    struct Node *_brother;
    uint32_t _wordcount;
} Node;

typedef struct Dictionary_t {
    Node *_firstnode;
} Dictionary_t;

typedef Dictionary_t* Dictionary;

Dictionary newDictionary();
void dictionaryInsert(Dictionary dict, const char* word);
void dictionaryRemove(Dictionary dict, const char* word);
size_t dictionaryContains(Dictionary dict, const char* str);
void printDictionary(Dictionary dict);
void freeDictionary(Dictionary dict);

#endif
