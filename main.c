#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "./dynamic_string/dynamic_string.h"

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define VOWELS "AEIOU"
#define CONSONANTS "BCDFGHJKLMNPQRSTVWXYZ"

#define TEST(func, ...)                                                                            \
    func(__VA_ARGS__);                                                                             \
    printf("%s(%s)\n\t", #func, #__VA_ARGS__);                                                     \
    string_print_debug(&s);                                                                        \
    puts("");

void test_constructors();
void test_append(String str);
void test_concat(String str);
void test_set(String str);
void test_substring(String str);

int main(void) {
    size_t len = 5;
    for(long i = -10; i <= 10; i++) {
        size_t u_index = string_normalize_index(len, i);
        printf("%ld -> %lu\n", i, u_index);
    }

    test_constructors();

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
    string_free(&s);

    String res = string_from_cstr_intersection("ABC", "ABCD", 10);
    printf("value: '%s', len: %lu\n", res.value, res.length);
    string_free(&res);

    res = string_from_cstr_intersection("ABCD", "ABC", 10);
    printf("value: '%s', len: %lu\n", res.value, res.length);
    string_free(&res);

    s = string_from_cstr("Hello, World!");
    printf("value: '%s', len: %lu\n", s.value, s.length);

    String sub = string_substring(&s, 6, 8);
    printf("value: '%s', len: %lu\n", sub.value, sub.length);
    string_free(&sub);

    sub = string_substring(&s, 0, 100);
    printf("value: '%s', len: %lu\n", sub.value, sub.length);
    string_free(&sub);

    sub = string_substring(&s, -3, -1);
    printf("value: '%s', len: %lu\n", sub.value, sub.length);
    string_free(&sub);
    string_free(&s);

    return 0;
}

void test_constructors() {
    printf("=========Initialization=========\n");
    String s = string_new_with_cap(10);
    printf("string_new_with_cap(10)\n\t");
    string_print_debug(&s);
    assert(strcmp(s.value, "") == 0 && s.length == 0);
    string_free(&s);
    puts("");

    s = string_new();
    printf("string_new()\n\t");
    string_print_debug(&s);
    assert(strcmp(s.value, "") == 0 && s.length == 0);
    string_free(&s);
    puts("");

    s = TEST(string_from_cstr, "");
    assert(strcmp(s.value, "") == 0 && s.length == 0);
    string_free(&s);

    s = TEST(string_from_cstr, "Hello, World!");
    assert(strcmp(s.value, "Hello, World!") == 0 && s.length == 13);
    string_free(&s);

    s = TEST(string_from_cstr, "\0\0\0\0");
    assert(strcmp(s.value, "") == 0 && s.length == 0);
    string_free(&s);

    char* cstr = "Hello, World!";
    s = TEST(string_from_cstr_sub, cstr, -2, -1);
    assert(strcmp(s.value, "d!") == 0 && s.length == 2);
    string_free(&s);

    s = TEST(string_from_cstr_sub, cstr, -10, -5);
    assert(strcmp(s.value, "lo, Wo") == 0 && s.length == 6);
    string_free(&s);

    s = TEST(string_from_cstr_sub, cstr, 0, -5);
    assert(strcmp(s.value, "Hello, Wo") == 0 && s.length == 9);
    string_free(&s);

    s = TEST(string_from_cstr_sub, cstr, 10, -5);
    assert(strcmp(s.value, "") == 0 && s.length == 0);
    string_free(&s);

    s = TEST(string_from_cstr_sub, cstr, 2, 5);
    assert(strcmp(s.value, "llo,") == 0 && s.length == 4);
    string_free(&s);

    s = TEST(string_from_cstr_intersection, "ABCDEFG", "CDEF", 0);
    assert(strcmp(s.value, "CDEF") == 0 && s.length == 4);
    string_free(&s);

    s = TEST(string_from_cstr_intersection, ALPHABET, VOWELS, 0);
    assert(strcmp(s.value, VOWELS) == 0 && s.length == 5);
    string_free(&s);

    s = TEST(string_from_cstr_intersection, ALPHABET, CONSONANTS, 10);
    assert(strcmp(s.value, "BCDFGHJKLM") == 0 && s.length == 10);
    string_free(&s);

    s = TEST(string_from_cstr_intersection, "Hello, World!", "Hello, Warudo", 0);
    assert(strcmp(s.value, "Hello, World") == 0 && s.length == 12);
    string_free(&s);

    printf("================================\n\n\n");
}
