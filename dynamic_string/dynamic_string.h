#include <stddef.h>

#ifndef DYNAMIC_STRING
#define DYNAMIC_STRING

typedef struct {
    char* value;
    size_t capacity;
    size_t len;
} String;

String string_init(const char* cstr);
void string_clear(String* p_str);
void string_set(String* p_str, const char* cstr);
void string_append(String* p_str, const char chr);
void string_concat(String* p_str, const char* cstr);
void string_free(String str);

#endif
