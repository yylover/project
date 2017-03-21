#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "../include/hash.h"

int foreachDisplay( const void *key, void *val, void *userptr) {
    printf("%s %s\n", (char *)key, (char *)val);
    return 0;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
HashTable *ht[2];

int indexOrg = 0;

void *thread1(void *data) {
    while (1) {
        HashTable *t = NULL;
        for (int i = 0; i < 1000; i++) {
            char str[10];
            sprintf(str, "%d", i);
            pthread_mutex_lock(&mutex);
            t = (HashTable *)(ht[indexOrg]);
            hashSet((HashTable *)t, str, str);
            // printf("%d\n", t->size);

            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

void *pthread2(void *data) {
    while (1) {
        sleep(2);

        pthread_mutex_lock(&mutex);
        int oldindex = indexOrg;
        indexOrg = (indexOrg + 1) % 2;
        pthread_mutex_unlock(&mutex);

        hashClear(ht[oldindex]);
        printf("%d %d\n", oldindex, (ht[oldindex])->size);
        // hashForEach(ht[oldindex], foreachDisplay, NULL);
    }
}

int main() {

    ht[0] = hashCreate(32);
    ht[1] = hashCreate(32);

    pthread_t t[6];

    if (pthread_create(&t[0], NULL, thread1, ht) != 0) {
        exit(0);
    }
    //
    if (pthread_create(&t[1], NULL, thread1, ht) != 0) {
        exit(0);
    }
    //
    if (pthread_create(&t[2], NULL, thread1, ht) != 0) {
        exit(0);
    }

    if (pthread_create(&t[3], NULL, pthread2, ht) != 0) {
        exit(0);
    }
    printf("线程创建成功\n");
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    printf("exit\n");

    // for (int i = 0; i < 100; i++) {
    //     char t[10];
    //     sprintf(t, "%d", i);
    //     hashSet(ht, t, t);
    // }
    //
    // printf("%d\n", ht->capacity);
    // printf("%d\n", ht->size);
    //
    // hashForEach(ht, foreachDisplay, NULL);
    //
    // for (int i = 0; i < 100; i++) {
    //     char t[10];
    //     sprintf(t, "%d", i);
    //     hashSet(ht, t, t);
    //     hashRemove(ht, t);
    // }

    // hashClear(ht);
    // printf("%d\n", ht->capacity);
    // printf("%d\n", ht->size);

    return 0;
}
