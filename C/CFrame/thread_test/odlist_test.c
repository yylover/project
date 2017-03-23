#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "../include/odlist.h"

// int foreachDisplay(const msd_hash_entry_t *entry, void *userptr) {
    // printf("%s %s\n", (char *)entry->key, (char *)entry->val);
    // return 0;
// }

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
msd_dlist_t *ht[2];
int indexOrg = 0;

typedef struct data {
    int i;
    char *str;
} Data;

void *thread1(void *data) {
    while (1) {
        msd_dlist_t *t = NULL;
        for (int i = 0; i < 100000; i++) {
            char str[10];
            sprintf(str, "%d", i);
            pthread_mutex_lock(&mutex);
            t = (msd_dlist_t *)(ht[indexOrg]);
            Data *d = (Data *) calloc(1, sizeof(*d));
            d->i = i;
            d->str = strdup(str);
            msd_dlist_add_node_tail(t, d);
            // printf("%d\n", t->count);

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

        msd_dlist_clear(ht[oldindex]);
        printf("%d %d\n", oldindex, (ht[oldindex])->len);
        // hashForEach(ht[oldindex], foreachDisplay, NULL);
    }
    pthread_exit(NULL);
}

void freeData(void *data) {
    Data *t = (Data*) data;
    if (t->str) {
        free(t->str);
    }
    free(t);
}

int main() {

    ht[0] = msd_dlist_init();
    ht[1] = msd_dlist_init();

    // msd_dlist_set_dup(ht[0],  (void *)strdup);
    msd_dlist_set_free(ht[0], freeData);

    // msd_dlist_set_dup(ht[1],  (void *)strdup);
    msd_dlist_set_free(ht[1], freeData);
    // MSD_HASH_SET_FREE_KEY(ht[0], msd_hash_def_free);
    // MSD_HASH_SET_FREE_VAL(ht[0], msd_hash_def_free);
    // MSD_HASH_SET_SET_KEY(ht[0], msd_hash_def_set);
    // MSD_HASH_SET_SET_VAL(ht[0], msd_hash_def_set);
    // MSD_HASH_SET_KEYCMP(ht[0], msd_hash_def_cmp);

    // MSD_HASH_SET_FREE_KEY(ht[1], msd_hash_def_free);
    // MSD_HASH_SET_FREE_VAL(ht[1], msd_hash_def_free);
    // MSD_HASH_SET_SET_KEY(ht[1], msd_hash_def_set);
    // MSD_HASH_SET_SET_VAL(ht[1], msd_hash_def_set);
    // MSD_HASH_SET_KEYCMP(ht[1], msd_hash_def_cmp);



    pthread_t t[6];

    if (pthread_create(&t[0], NULL, thread1, ht) != 0) {
        exit(0);
    }
    // //
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

    // for (int i = 0; i < 1000000; i++) {
    //     char t[10];
    //     sprintf(t, "%d", i);
    //     msd_hash_insert(ht[0], t, t);
    // }

    // printf("%d\n", ht[0]->slots);
    // printf("%d\n", ht[0]->count);

    // msd_hash_foreach(ht[0], foreachDisplay, NULL);
    // msd_hash_clear(ht[0]);
    // printf("%d\n", ht[0]->slots);
    // printf("%d\n", ht[0]->count);

    // msd_hash_foreach(ht[0], foreachDisplay, NULL);

    // printf("%d\n", ht[0]->slots);
    // printf("%d\n", ht[0]->count);

    // msd_hash_entry_t *he = calloc(1, sizeof(*he));
    // he->val = "123";
    // he->key = "123";
    // he->next = NULL;
    //
    // msd_hash_entry_t *he2 = calloc(1, sizeof(*he));
    // he2->val = "456";
    // he2->key = "456";
    // he->next = he;

    // msd_hash_entry_t *h = he2;
    // free(h);
    // free(he2);

    // printf("%s %s\n", he2->key, he2->val);
    // printf("%s %s\n", h->key, h->val);



    // hashClear(ht);
    // printf("%d\n", ht->capacity);
    // printf("%d\n", ht->size);

    return 0;
}
