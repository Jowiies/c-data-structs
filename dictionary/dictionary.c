#include "dictionary.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Returns a pointer to a new dynamically allocated node
Node *newNode(const char c, const char* desc, Node *child, Node *brother) 
{
    Node *node = (Node*)malloc(sizeof(Node));
    
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error: Couldn't create a new node");
        exit(1);  
    }
    
    node->_brother = brother;
    node->_child = child;
    node->_key = c;
    node->_value = NULL;
    
    if (desc != NULL) {
        node->_value = (const char*)malloc((strlen(desc) + 1) * sizeof(char));
        
        if (node->_value == NULL) {
            fprintf(stderr, "Memory allocation error: Couldn't create a description");
            exit(1);  
        }
        
        node->_value = strcpy((char*)node->_value, desc);
    }
    
    return node;
}

Node *insertNode(Node *ptr, const char* word, const char* desc, const int *size, int it)
{

    if (it == *size) {
        if (ptr == NULL) {
            ptr = newNode(ENDCHAR, desc, NULL, NULL);
        }
        else if (ptr->_key != ENDCHAR) {
            Node *newnode = newNode(ENDCHAR, desc, NULL, ptr);
            ptr = newnode;
        }
        return ptr;
    }
    int c = tolower(word[it]);

    if (ptr == NULL) {
        ptr = newNode(c, NULL, NULL, NULL);
    }

    if (ptr->_key > c) {
        Node* newnode = newNode(c, NULL, NULL, ptr);
        ptr = newnode;
        ptr->_child = insertNode(ptr->_child, word, desc, size, it+1);
    }
    else if (ptr->_key < c) {
        ptr->_brother = insertNode(ptr->_brother, word, desc, size, it);
    }
    else {
        ptr->_child = insertNode(ptr->_child, word, desc, size, it+1);
    }

    return ptr;
}

void freeNodes(Node *ptr)
{
    if (ptr == NULL)
        return;
    
    freeNodes(ptr->_child);
    freeNodes(ptr->_brother);
    free((void*)ptr->_value);
    free(ptr);
}

Node* findNode(Node *ptr, const char* word, size_t* size, int it)
{
    if (ptr != NULL) {
        char c = tolower(word[it]);
        if (it == *size)
            return (ptr->_key == ENDCHAR) ? ptr : NULL;
        
        if (ptr->_key < c)
            return findNode(ptr->_brother, word, size, it);
        
        if (ptr->_key == c)
            return findNode(ptr->_child, word, size, it+1);
    }
    
    return NULL;
}

Dictionary newDictionary()
{
   Dictionary d = (Dictionary)malloc(sizeof(Dictionary));
   
   if (!d) {
       fprintf(stderr, "Memory allocation error: Couldn't create the dictionary");
       exit(1);  
   }
   
   d->_firstnode = NULL;
   
   return d;
}

void dictionaryInsert(Dictionary dict, const char* word, const char* description)
{
    if (word == NULL) {
        fprintf(stderr, "Insertion Error: The word was NULL");
        exit(1);
    }
    
    if (!description) {
        fprintf(stderr, "Insertion Error: The description was NULL");
        exit(1);
    
    }
    
    int wordsize = strlen(word), iter = 0;
    dict->_firstnode = insertNode(dict->_firstnode, word,description, &wordsize, iter);
}

const char* dictionarySearch(Dictionary dict, const char* word) 
{
    size_t wordsize = strlen(word);
    int iter = 0;
    
    Node *node = findNode(dict->_firstnode, word, &wordsize, iter);
    
    return (node != NULL) ? node->_value : NULL;
}

void freeDictionary(Dictionary dict)
{
    freeNodes(dict->_firstnode);
    free(dict);
}
