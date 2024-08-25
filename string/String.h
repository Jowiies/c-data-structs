#ifndef STRING_H
#define STRING_H

#include <stddef.h>

typedef struct String{
    const char* _s;
    size_t _length;

    void (*setData)(struct String*, const char*);
    void (*addStr)(struct String*, const char*);
    void (*sinkStr)(struct String*, size_t);
    void (*deleteStr)(struct String*);
} String;

// Pre: TRUE
// Post: _this->_s = str
void setData(String* _this, const char* str);

// Pre: TRUE
// Post: _this->_s += str
void addStr(String* _this, const char* str);

// Pre: TRUE
// Post: sinks _this length size times
void sinkStr(String* _this, size_t size);

// Pre: TRUE
// Post: frees _this memory
void deleteStr(String* _this);

// Pre: TRUE
// Post: creates a new String
String* newString(const char* str);

#endif /* STRING_H */
