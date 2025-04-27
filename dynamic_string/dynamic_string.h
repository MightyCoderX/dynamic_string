#include <stdbool.h>
#include <stddef.h>

#ifndef DYNAMIC_STRING
#define DYNAMIC_STRING

typedef struct {
    char* value;
    size_t capacity;
    size_t length;
} String;

size_t string_normalize_index(size_t len, long index);

/*
 * Create new string with initial capacity
 */
String string_new_with_cap(size_t capacity);

/*
 * Create new string with initial capacity 0
 */
String string_new(void);

/*
 * Initialize string from C string
 */
String string_from_cstr(const char* cstr);

/*
 * Initialize string from a substring of a
 * C string delimited by the indexes (both included)
 */
String string_from_cstr_sub(const char* cstr, long start, long end);

/*
 * Initialize String from "intersection" between two c strings
 */
String string_from_cstr_intersection(const char* cstr1, const char* cstr2, long max_len);

void string_extend(String* p_str, size_t new_len, bool copy_old);

void string_clear(String* p_str);
void string_set(String* p_str, const char* cstr);

void string_append(String* p_str, const char chr);
void string_concat(String* p_str, const char* cstr);

String string_substring(const String* p_str, long start, long end);

void string_upper(String* p_str);
void string_lower(String* p_str);

void string_print_debug(const String* p_str);

char* string_to_cstr(const String* p_str);

char string_get_char(const String* p_str, long index);
void string_set_char(String* p_str, long index, char chr);

void string_free(String* p_str);

#endif
