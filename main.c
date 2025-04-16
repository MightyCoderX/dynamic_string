#include <stdio.h>

#include "./dynamic_string/dynamic_string.h"

int main(void) {
    String s = string_init("Hello");
    printf("value: %s, len: %lu\n", s.value, s.len);

    for(int i = 65; i < (65 + 26); i++) {
        printf("%c\n", i);
        string_append(&s, i);
    }

    printf("%s\n", s.value);
    return 0;
}
