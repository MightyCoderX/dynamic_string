#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./dynamic_string.h"

String string_init(const char* cstr) {
    size_t len = strlen(cstr) + 1;
    size_t capacity = len + 10;
    String new = { malloc(capacity), capacity, len };

    for(size_t i = 0; i < len; i++) {
        new.value[i] = cstr[i];
    }

    return new;
}

void string_clear(String* p_str) {
    for(size_t i = 0; i < p_str->len; i++) {
        p_str->value[i] = '\0';
    }
    p_str->len = 0;
}

void string_set(String* p_str, const char* cstr) {
    size_t cstr_len = strlen(cstr);

    string_clear(p_str);

    if(cstr_len > p_str->capacity) {
        char* old_value = p_str->value;
        char* new_value = malloc(cstr_len);

        free(old_value);

        p_str->value = new_value;
        p_str->capacity = cstr_len;
    }

    for(size_t i = 0; i < cstr_len; i++) {
        p_str->value[i] = cstr[i];
    }

    p_str->len = cstr_len;
}

void string_append(String* p_str, const char chr) {
    size_t new_len = p_str->len + 1;

    if(new_len > p_str->capacity) {
        char* old_value = p_str->value;
        char* new_value = malloc(new_len);

        memcpy(new_value, old_value, p_str->len);
        free(old_value);

        p_str->value = new_value;
        p_str->capacity = new_len;
    }

    p_str->value[p_str->len] = chr;
    p_str->value[p_str->len + 1] = '\0';
    p_str->len = new_len;
}

void string_concat(String* p_str, const char* cstr) {
    size_t cstr_len = strlen(cstr);

    size_t new_len = p_str->len + cstr_len;

    if(new_len > p_str->capacity) {
        char* old_value = p_str->value;
        char* new_value = malloc(new_len);

        memcpy(new_value, old_value, p_str->len);
        free(old_value);

        p_str->value = new_value;
        p_str->capacity = new_len;
    }

    for(size_t i = 0; i < cstr_len; i++) {
        p_str->value[p_str->len - 1] = cstr[i];
        p_str->len++;
    }
}

void string_free(String* p_str) {
    free(p_str->value);
    p_str->value = NULL;
    p_str->len = 0;
    p_str->capacity = 0;
}
