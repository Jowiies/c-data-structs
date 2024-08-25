#include "String.h"
#include <stdlib.h>
#include <stdio.h>

String* newString(const char* str)
{
    String *string = (String*)malloc(sizeof(String));
    if (!string) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(-1);
    }
    string->_s = NULL;
    string->_length = 0;

    string->addStr = addStr;
    string->sinkStr = sinkStr;
    string->setData = setData;
    string->deleteStr = deleteStr;
    
    string->setData(string, str);
   
    return string;
}

void addStr(String* _this, const char* str)
{
    size_t len = 0;
    for (; str[len] != '\0'; ++len);
    char* cpy = (char*)malloc((_this->_length + len + 1) * sizeof(char));
    if (cpy == NULL) {
        fprintf(stderr, "Memory allocation error!\n");
        exit(-1);
    }
    
    char *ptr = cpy;
    char *deleteptr = (char*)_this->_s;
    while (*_this->_s != '\0') {
        *ptr = *_this->_s;
        ++ptr;
        ++_this->_s;
    }
    while (*str != '\0') {
        *ptr = *str;
        ++ptr;
        ++str;
    }
    *ptr = '\0';

    _this->_length += len;
    free((char*)deleteptr);
    _this->_s = cpy;

}
void sinkStr(String* _this, size_t size)
{
    size_t len = (_this->_length - size < 0) ? 0 : _this->_length - size;
    char *cpy = (char*)malloc((len + 1) * sizeof(char));
    for (size_t i = 0; i < len; ++i){
        cpy[i] = _this->_s[i];
    }
    cpy[len] = '\0';
    free((char*)_this->_s);
    _this->_s = cpy;
    _this->_length = len;
}

void setData(String *_this, const char *str)
{
    if (_this->_s)
        free((char*)_this->_s);
    
    size_t len = 0;
    for (; str[len] != '\0'; ++len);
    _this->_length = len;

    char* cpy = (char*)malloc((len + 1) * sizeof(char));

    if (cpy == NULL) {
        fprintf(stderr, "Error while mem allocation\n");
        exit(-1);
    }
    else {
        char* ptr = cpy;
        while (*str != '\0') {
            *cpy = *str;
            cpy++;
            str++;
        }
        *cpy = '\0';
        _this->_s = ptr;
    }
}

void deleteStr(String *_this)
{
    _this->_length = 0;
    free((char*)_this->_s);
    free((String*)_this);
}
