#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <google/cmockery.h>
#include <stdio.h>

#include "../include/string.h"


int my_print(void* elem, void* d)
{
    // printf("%d %d \n", d1->value, d2->value);
    return 0;
}

void test_stringCreate(void **state) {
    string *str = stringNew("hello");
    assert_int_equal(str->len, 5);
    assert_int_equal(str->size, 6);
    stringFree(str);

    str = stringNew("");
    assert_int_equal(str->len, 0);
    assert_int_equal(str->size, 1);
    stringFree(str);

    str = stringNewEmpty();
    assert_int_equal(str->len, 0);
    assert_int_equal(str->size, 1);
    stringFree(str);
}

void test_stringCat(void **state) {
    char *hello = "hello";
    string *str = stringNewEmpty();
    string *strNew = stringCat(&str, hello);
    assert_int_equal(strNew->len, 5);
    assert_int_equal(strNew->size, 6);
    assert_true(strNew == str);
    stringClear(strNew);
    assert_int_equal(strNew->len, 0);
    assert_int_equal(strNew->size, 6);
    // stringFree(strNew);

    string *str2 = stringNew(hello);
    strNew = stringCatString(&strNew, str2);
    assert_int_equal(strNew->len, 5);
    assert_int_equal(strNew->size, 6);
    assert_true(strNew == str);
    stringClear(strNew);
    assert_int_equal(strNew->len, 0);
    assert_int_equal(strNew->size, 6);
    stringFree(str2);


    //stringCatSprintf
    str = stringNew("H");
    strNew = stringCatSprintf(&str, "%s", "helloworld");
    assert_int_equal(strNew->len, 11);
    assert_int_equal(strNew->size, 12);
    assert_true(strNew == str);
    stringClear(strNew);
    assert_int_equal(strNew->len, 0);
    assert_int_equal(strNew->size, 12);
}

void test_stringCpy(void **state) {
    string *str = stringNew("H");
    str = stringCpy(&str, "helloworld");
    assert_int_equal(str->len, 10);
    assert_int_equal(str->size, 11);
}

void test_stringLowerUpper(void **state) {
    string *str = stringNew("H");
    stringToLower(str);
    assert_string_equal(str->buf, "h");

    stringToUpper(str);
    assert_string_equal(str->buf, "H");
}

void test_stringCmp(void **state) {
    string *str1 = stringNew("A");
    string *str2 = stringNew("H");
    int res = stringCmp(str1, str2);
    assert_true(res < 0);
}

void test_stringTrim(void **state) {

    string *str = stringNew(" str !@ ");

    stringTrim(str, " !@#");
    assert_int_equal(str->len, 3);
    assert_int_equal(str->size, 9);
}


int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_stringCreate),
        unit_test(test_stringCpy),
        unit_test(test_stringCat),
        unit_test(test_stringLowerUpper),
        unit_test(test_stringCmp),
        unit_test(test_stringTrim),
    };
    return run_tests(tests);
}
