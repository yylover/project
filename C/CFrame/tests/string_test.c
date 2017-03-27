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

    str = stringNew("");
    assert_int_equal(str->len, 0);
    assert_int_equal(str->size, 1);

    str = stringNewEmpty();
    assert_int_equal(str->len, 0);
    assert_int_equal(str->size, 1);

    char *hello = "hello";
    string *strNew = stringCat(&str, hello);
    printf("%d \n", strNew == NULL);
    // assert_int_equal(strNew->len, 5);
    // assert_int_equal(strNew->size, 6);
    // assert_true(strNew == str);

    printf("%d %d %s\n", str->len, str->size, str->buf);
}


int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_stringCreate),
    };
    return run_tests(tests);
}
