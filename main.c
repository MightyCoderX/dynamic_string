#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "./dynamic_string/dynamic_string.h"

void test_initialization();
void test_append(String str);
void test_concat(String str);
void test_set(String str);
void test_substring(String str);

int main(void) {
    test_initialization();

    String s = string_from_cstr("Hello");
    printf("value: %s, len: %lu\n", s.value, s.length);

    for(int i = 'A'; i < ('A' + 26); i++) {
        string_append(&s, i);
    }
    printf("value: '%s', len: %lu\n", s.value, s.length);

    string_concat(&s, " bruh");
    printf("value: '%s', len: %lu\n", s.value, s.length);

    // string_clear(&s);
    string_set(&s, "lol");
    printf("value: '%s', len: %lu\n", s.value, s.length);

    string_set(&s, "Hello, World!");
    printf("value: '%s', len: %lu\n", s.value, s.length);

    string_append(&s, 'l');
    printf("value: '%s', len: %lu\n", s.value, s.length);

    String res = string_from_cstr_intersection("ABC", "ABCD", 10);
    printf("value: '%s', len: %lu\n", res.value, res.length);

    res = string_from_cstr_intersection("ABCD", "ABC", 10);
    printf("value: '%s', len: %lu\n", res.value, res.length);

    s = string_from_cstr("Hello, World!");
    printf("value: '%s', len: %lu\n", s.value, s.length);

    String sub = string_substring(&s, 6, 8);
    printf("value: '%s', len: %lu\n", sub.value, sub.length);

    sub = string_substring(&s, 0, 100);
    printf("value: '%s', len: %lu\n", sub.value, sub.length);

    sub = string_substring(&s, -3, -1);
    printf("value: '%s', len: %lu\n", sub.value, sub.length);

    return 0;
}

void test_initialization() {
    printf("=========Initialization=========\n");
    String s = string_new_with_cap(10);
    printf("string_new_with_cap(10): value: '%s', len: %lu\n", s.value, s.length);

    s = string_new();
    printf("string_new(): value: '%s', len: %lu\n", s.value, s.length);

    s = string_from_cstr("");
    printf("string_from_cstr(\"\"): value: '%s', len: %lu\n", s.value, s.length);

    s = string_from_cstr("Hello, World!");
    printf("string_from_cstr(\"Hello, World!\"): value: '%s', len: %lu\n", s.value, s.length);

    s = string_from_cstr("\0\0\0\0");
    printf("string_from_cstr(\"\\0\\0\\0\\0\"): value: '%s', len: %lu\n", s.value, s.length);

    char* cstr = "Hello, World!";
    s = string_from_cstr_sub(cstr, -2, -1);
    assert(strcmp(s.value, "d!") == 0 && s.length == 2);

    s = string_from_cstr_sub(cstr, -10, -5);
    assert(strcmp(s.value, "lo, Wo") == 0 && s.length == 6);

    s = string_from_cstr_sub(cstr, 0, -5);
    assert(strcmp(s.value, "Hello, Wo") == 0 && s.length == 9);

    s = string_from_cstr_sub(cstr, 10, -5);
    assert(strcmp(s.value, "") == 0 && s.length == 0);

    s = string_from_cstr_sub(cstr, 2, 5);
    assert(strcmp(s.value, "llo,") == 0 && s.length == 4);

    char* cstr1 = "ABCDEFG";
    char* cstr2 = "CDEF";
    s = string_from_cstr_intersection(cstr1, cstr2, 0);
    assert(strcmp(s.value, "CDEF") == 0 && s.length == 4);

    cstr1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cstr2 = "AEIOU";
    s = string_from_cstr_intersection(cstr1, cstr2, 0);
    assert(strcmp(s.value, "AEIOU") == 0 && s.length == 5);

    cstr1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cstr2 = "BCDFGHJKLMNPQRSTVWXYZ";
    s = string_from_cstr_intersection(cstr1, cstr2, 0);
    assert(strcmp(s.value, "BCDFGHJKLMNPQRSTVWXYZ") == 0 && s.length == 21);

    cstr1 = "Hello, World!";
    cstr2 = "Hello, Warudo";
    s = string_from_cstr_intersection(cstr1, cstr2, 0);
    assert(strcmp(s.value, "Hello, World") == 0 && s.length == 12);

    string_free(&s);

    printf("================================\n\n\n");
}
