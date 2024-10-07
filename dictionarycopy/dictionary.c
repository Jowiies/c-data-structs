#include "dictionary.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//=========================================================================================
//===============================ALLOCATION FUNCTIONS======================================
//=========================================================================================

Node *newNode(const char c, Node *child, Node *brother) 
{
    Node *node = (Node*)malloc(sizeof(Node));
    
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error: Couldn't create a new node");
        exit(1);  
    }
    
    node->_brother = brother;
    node->_child = child;
    node->_key = (c != ENDCHAR) ? tolower(c) : c;
    node->_wordcount = (c == ENDCHAR) ? 1 : 0;
    
    return node;
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

//=========================================================================================
//================================DEALLOCATION FUNCTIONS===================================
//=========================================================================================

void freeNodes(Node *ptr)
{
    if (ptr == NULL)
        return;
    
    freeNodes(ptr->_child);
    freeNodes(ptr->_brother);
    free(ptr);
}

void freeDictionary(Dictionary dict)
{
    freeNodes(dict->_firstnode);
    free(dict);
}

//=========================================================================================
//=================================PRINT FUNCTIONS=========================================
//=========================================================================================

void printNodes(Node *ptr, char buffer[], uint32_t *it)
{
    if (ptr == NULL)
        return;

    if (ptr->_key == ENDCHAR) {
        buffer[*it] = '\0';
        printf(" - %s --> %d times.\n", buffer, ptr->_wordcount);
    }


    buffer[*it] = ptr->_key;
    (*it)++;

    printNodes(ptr->_child, buffer, it);
    (*it)--;
    printNodes(ptr->_brother, buffer, it);
}

void printDictionary(Dictionary dict)
{
    char buffer[48] = {0};
    uint32_t iter = 0;
    printNodes(dict->_firstnode, buffer, &iter); 
}

//=========================================================================================
//=========================================================================================
//=========================================================================================


//Returns a pointer to a new dynamically allocated node
Node *insertNode(Node *ptr, const char* word, const int *size, int it)
{

    if (it == *size) {
        if (ptr == NULL) {
            ptr = newNode(ENDCHAR, NULL, NULL);
        }
        else if (ptr->_key == ENDCHAR) {
            ptr->_wordcount++;
        }
        else {
            Node *newnode = newNode(ENDCHAR, NULL, ptr);
            ptr = newnode;
        }
        return ptr;
    }
    int c = tolower(word[it]);

    if (ptr == NULL) {
        ptr = newNode(c, NULL, NULL);
    }

    if (ptr->_key > c) {
        Node* newnode = newNode(c, NULL, ptr);
        ptr = newnode;
        ptr->_child = insertNode(ptr->_child, word, size, it+1);
    }
    else if (ptr->_key < c) {
        ptr->_brother = insertNode(ptr->_brother, word, size, it);
    }
    else {
        ptr->_child = insertNode(ptr->_child, word, size, it+1);
    }

    return ptr;
}


Node* findNode(Node *ptr, const char* word, size_t* size, size_t it)
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

void dictionaryInsert(Dictionary dict, const char* word)
{
    if (word == NULL) {
        fprintf(stderr, "Insertion Error: The word was NULL");
        exit(1);
    }
    
    int wordsize = strlen(word), iter = 0;
    dict->_firstnode = insertNode(dict->_firstnode, word, &wordsize, iter);
}
