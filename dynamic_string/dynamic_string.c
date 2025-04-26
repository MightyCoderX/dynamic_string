#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./dynamic_string.h"

String string_new_with_cap(size_t capacity) {
    String new = { malloc(capacity), capacity, 0 };
    return new;
}

String string_new() {
    return string_new_with_cap(0);
}

String string_from_cstr(const char* cstr) {
    size_t len = strlen(cstr);
    size_t capacity = len + 10;
    String new = { malloc(capacity), capacity, len };

    for(size_t i = 0; i < len; i++) {
        new.value[i] = cstr[i];
    }

    return new;
}

String string_from_cstr_sub(const char* cstr, long start, long end) {
    size_t len = strlen(cstr);

    size_t u_end;
    if(end < 0) {
        if(len + end + 1 > 0) {
            u_end = len + end + 1;
        } else {
            u_end = 0;
        }
    } else {
        u_end = end + 1;
    }

    size_t u_start = 0;
    if(start < 0) {
        if(len + start > 0) {
            u_start = len + start;
        } else {
            u_start = 0;
        }
    } else {
        u_start = start;
    }

    String sub = string_from_cstr("");

    if(u_start > u_end || u_end > len) {
        return sub;
    }

    for(size_t i = u_start; i < u_end; i++) {
        string_append(&sub, cstr[i]);
    }

    return sub;
}

String string_from_cstr_intersection(const char* cstr1, const char* cstr2, long max_len) {
    size_t cstr1_len = strlen(cstr1);
    size_t cstr2_len = strlen(cstr2);

    if(cstr1_len > cstr2_len) { // sort in ascending order
        const char* tmp = cstr1;
        cstr1 = cstr2;
        cstr2 = tmp;
    }

    cstr1_len = strlen(cstr1);
    cstr2_len = strlen(cstr2);

    size_t u_max_len = max_len <= 0 ? strlen(cstr1) : max_len;
    String intersection = string_new_with_cap(u_max_len);

    size_t i = 0;
    char c;
    do {
        c = cstr1[i];
        if(strchr(cstr2, c) != NULL) {
            string_append(&intersection, c);
        }

        i++;

    } while(c != '\0' && i < cstr1_len && intersection.length < u_max_len);

    return intersection;
}

void string_extend(String* p_str, size_t new_len, bool should_copy_old) {
    char* old_pointer = p_str->value;
    char* new_pointer;

    if(should_copy_old && p_str->length > 0) {
        // printf("value: '%s', old_len: %lu, new_len: %lu\n", p_str->value, p_str->length, new_len);
        new_pointer = realloc(old_pointer, new_len);
    } else {
        new_pointer = malloc(new_len);
        free(old_pointer);
    }

    p_str->value = new_pointer;
    p_str->capacity = new_len;
}

void string_clear(String* p_str) {
    for(size_t i = 0; i < p_str->length; i++) {
        p_str->value[i] = '\0';
    }
    p_str->length = 0;
}

void string_set(String* p_str, const char* cstr) {
    size_t cstr_len = strlen(cstr);

    string_clear(p_str);

    if(cstr_len > p_str->capacity) {
        string_extend(p_str, cstr_len, false);
    }

    for(size_t i = 0; i < cstr_len; i++) {
        p_str->value[i] = cstr[i];
    }

    p_str->length = cstr_len;
}

void string_append(String* p_str, const char chr) {
    size_t new_len = p_str->length + 1;

    if(new_len > p_str->capacity) {
        string_extend(p_str, new_len + 1, true);
    }

    p_str->value[p_str->length] = chr;
    p_str->value[p_str->length + 1] = '\0';
    p_str->length = new_len;
}

void string_concat(String* p_str, const char* cstr) {
    size_t cstr_len = strlen(cstr);

    size_t new_len = p_str->length + cstr_len;

    if(new_len > p_str->capacity) {
        string_extend(p_str, new_len, true);
    }

    for(size_t i = 0; i < cstr_len; i++) {
        p_str->value[p_str->length] = cstr[i];
        p_str->length++;
    }
}

String string_substring(String* p_str, long start, long end) {
    return string_from_cstr_sub(p_str->value, start, end);
}

void string_upper(String* p_str) {
    for(size_t i = 0; i < p_str->length; i++) {
        p_str->value[i] = toupper(p_str->value[i]);
    }
}

void string_lower(String* p_str) {
    for(size_t i = 0; i < p_str->length; i++) {
        p_str->value[i] = tolower(p_str->value[i]);
    }
}

void string_free(String* p_str) {
    free(p_str->value);
    p_str->value = NULL;
    p_str->length = 0;
    p_str->capacity = 0;
}
