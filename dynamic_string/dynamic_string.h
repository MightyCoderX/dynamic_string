#include <stddef.h>

#ifndef DYNAMIC_STRING
#define DYNAMIC_STRING

typedef struct {
    char* value;
    size_t capacity;
    size_t len;
} String;

String string_init(const char* cstr);
void string_append(String str, const char* cstr);
void string_free(String str);

#endif
