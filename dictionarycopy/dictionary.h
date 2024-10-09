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
    uint32_t _uniqueCount;
    uint32_t _totalwords;
} Dictionary_t;

typedef Dictionary_t* Dictionary;

Dictionary newDictionary();
void dictionaryInsert(Dictionary dict, const char* word);
void dictionaryRemove(Dictionary dict, const char* word);
void printDictionary(Dictionary dict);
void freeDictionary(Dictionary dict);

uint32_t getUniqueWordCount(Dictionary dict);
uint32_t getTotalWords(Dictionary dict);

#endif
