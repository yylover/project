#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <google/cmockery.h>
#include <stdio.h>

#include "../include/adlist.h"
#include "../include/vector.h"

void print(list *adlist) {
    listNode *node = adlist->head;
    while (node) {
        printf("%s\n", node->value);
        node = node->next;
    }
}

void test_add(void **state) {
    // assert_int_equal(add(3, 3), 6);
    // assert_int_not_equal(add(3, 3), 5);
}

void test_listCreate() {
    list *adlist = listCreate();
    assert_true(adlist != NULL);
    assert_int_equal(adlist->length, 0);
    assert_true(adlist->dup == NULL);
    assert_true(adlist->match == NULL);
    assert_true(adlist->free == NULL);
    assert_true(adlist->head == NULL);
    assert_true(adlist->tail == NULL);
}

void test_listRelease() {
    list *adlist = listCreate();
    listRelease(adlist);
    // assert_true(adlist == NULL);
}

void test_listAddNodeHeadAndTail() {
    list *adlist = listCreate();
    char * str = "hello";
    listAddNodeHead(adlist, str);

    assert_true(adlist->head != NULL);
    assert_true(adlist->tail != NULL);
    assert_true(adlist->head->next == NULL);
    assert_true(adlist->tail->prev == NULL);
    assert_int_equal(adlist->length, 1);
    assert_int_equal(0, strcmp("hello", adlist->head->value));

    char *str2 = "world";
    listAddNodeTail(adlist, str2);
    assert_int_equal(2, adlist->length);
    assert_int_equal(0, strcmp(str, adlist->head->value));
    assert_int_equal(0, strcmp(str2, adlist->tail->value));

    char *str3 = "two";
    listInsertNode(adlist, adlist->head, str3, 1);
    assert_int_equal(3, adlist->length);
    assert_int_equal(0, strcmp(str3, adlist->head->next->value));
    //
    char *str4 = "one";
    listInsertNode(adlist, adlist->head, str4, 0);
    assert_int_equal(4, adlist->length);
    assert_int_equal(0, strcmp(str4, adlist->head->value));

    print(adlist);

    listRotate(adlist);
    print(adlist);
    listRotate(adlist);

    list *dup = listDup(adlist);
    print(dup);

    //删除
    listDeleteNode(adlist, adlist->head->next);
    assert_int_equal(3, adlist->length);
    assert_int_equal(0, strcmp(str3, adlist->head->next->value));

    listDeleteNode(adlist, adlist->head);
    assert_int_equal(2, adlist->length);
    assert_int_equal(0, strcmp(str3, adlist->head->value));

    listDeleteNode(adlist, adlist->tail);
    assert_int_equal(1, adlist->length);
    assert_int_equal(0, strcmp(str3, adlist->tail->value));

    listNode *l = listSearchKey(adlist, str3);
    assert_int_equal(0, strcmp(str3, l->value));

    l = listSearchKey(adlist, str2);
    assert_true(l == NULL);

    l = listIndex(adlist, 0);
    assert_int_equal(0, strcmp(str3, l->value));

    l = listIndex(adlist, 1);
    assert_true(l == NULL);

    listRelease(adlist);
}

void test_vectorCreate() {
    vector *v = vectorCreate(10, sizeof(int));
}

int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_add),
        unit_test(test_listCreate),
        unit_test(test_listRelease),
        unit_test(test_listAddNodeHeadAndTail),
    };
    return run_tests(tests);
}
