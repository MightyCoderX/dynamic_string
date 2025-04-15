#include <stdio.h>

#include "./dynamic_string/dynamic_string.h"

int main(void) {
    String s = string_init("Hello");
    printf("%s\n", s.value);

    string_append(s, ", World!");

    printf("%s\n", s.value);
    return 0;
}
