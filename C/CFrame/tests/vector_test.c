#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <google/cmockery.h>
#include <stdio.h>

#include "../include/adlist.h"
#include "../include/vector.h"

typedef struct data {
    int value;
}data;

void print(list *adlist) {
    listNode *node = adlist->head;
    while (node) {
        printf("%s\n", node->value);
        node = node->next;
    }
}

void printVector(vector *v) {
    data *d;
    int i = 0;
    while (i < v->count) {
        d = vectorGetAt(v, i);
        printf("%d\n", d->value);
        i++;
    }
}

int vectorCmpFunc(const void *d1, const void *d2) {
    data *data1 = (data*)d1;
    data *data2 = (data*)d2;
    return data2->value - data1->value;
}

int my_print(void* elem, void* d)
{
    data *d1 = (data*)elem;
    data *d2 = (data*)d;
    printf("%d %d \n", d1->value, d2->value);
    return 0;
}

void test_vectorCreate(void **state) {
    vector *v = vectorCreate(16, sizeof(data));
    assert_int_equal(v->slots, 16);
    assert_int_equal(v->count, 0);
    assert_int_equal(v->sizeElem, sizeof(data));
    //
    data d1;
    d1.value = 2;
    vectorPush(v, &d1);
    assert_int_equal(v->count, 1);

    data d2;
    d2.value = 4;
    vectorPush(v, &d2);
    assert_int_equal(v->count, 2);

    data *d = vectorTop(v);
    printVector(v);

    d = vectorPop(v);
    assert_int_equal(d->value, 4);
    assert_int_equal(v->count, 1);

    data d3;
    d3.value = 6;
    vectorSetAt(v, 2, &d3);
    printVector(v);

    vectorSort(v, vectorCmpFunc);
    printVector(v);

    vectorEach(v, my_print, &d3);
}


int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_vectorCreate),
    };
    return run_tests(tests);
}
