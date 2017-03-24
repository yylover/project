#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct worker {
    void *priv_data;
    void (*freePrivData)(void*);
} worker;

void freePrivData(void *data) {
    printf("free \n");
    if (data) {
        free(data);
    }
}

int main () {
    worker *w = (worker*) malloc(sizeof(*w));
    w->priv_data = strdup("hello");
    w->freePrivData = freePrivData;
    w->freePrivData(w->priv_data);

    return 0;
}
