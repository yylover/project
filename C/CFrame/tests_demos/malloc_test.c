#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "../include/string.h"

typedef struct data {
    int t ;
} data;

int main() {
    data *d1 = (data* ) malloc(sizeof(*d1));
    data *d2 = (data* ) malloc(sizeof(*d1));

    printf("d1 address :%p\n", d1);
    printf("d2 address :%p\n", d2);

    data *d3 = (data*) realloc(d1, sizeof(data)*10);
    printf("d1 address :%p\n", d1);
    printf("d3 address :%p\n", d3);


    printf("stirng size: %lu\n", sizeof(string));
    string *str = malloc(sizeof(string) + 10+1); //为字符串分配的空间11
    printf("str :%p\n", str);
    printf("len :%p\n", &(str->len));
    printf("size :%p\n", &(str->size));
    printf("buf :%p\n", &(str->buf));


}
