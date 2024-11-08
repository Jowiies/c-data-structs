#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stddef.h>
#include <stdio.h>

#define ENDCHAR '#'

typedef struct Node {
    char _key;
    struct Node *_child;
    struct Node *_brother;
    const char* _value;
} Node;

typedef struct Dictionary_t {
    Node *_firstnode;
} Dictionary_t;

typedef Dictionary_t* Dictionary;

// retuns a pointer to an allocated void dictionary
Dictionary newDictionary();

// inserts a new word + description to the dictionary.
void dictionaryInsert(Dictionary dict, const char* word, const char* description);

// return a strin_view of the description of the word.
const char* dictionarySearch(Dictionary dict, const char* word);

// removes the word from the dictionary.
void dictionaryRemoveWord(Dictionary dict, const char* word);

// returns how many word start with str.
size_t dictionaryContains(Dictionary dict, const char* str);

void freeDictionary(Dictionary dict);

#endif
