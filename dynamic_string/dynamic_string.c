#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./dynamic_string.h"

String string_init(const char* cstr) {
    size_t len = strlen(cstr);
    String new = { malloc(len), len, len };

    for(size_t i = 0; i < len; i++) {
        new.value[i] = cstr[i];
    }

    return new;
}

void string_append(String str, const char* cstr) {
    size_t cstr_len = strlen(cstr);

    size_t new_len = str.len + cstr_len;

    if(new_len > str.capacity) {
        char* old_value = str.value;
        char* new_value = malloc(new_len);

        memcpy(new_value, old_value, str.len);
        printf("new_value: %s\n", new_value);
        free(old_value);

        str.value = new_value;
        str.capacity = new_len;
    }

    for(size_t i = 0; i < cstr_len; i++) {
        str.value[str.len] = cstr[i];
        str.len++;
    }
}

void string_free(String str) {
    free(str.value);
    str.value = NULL;
    str.len = 0;
    str.capacity = 0;
}
