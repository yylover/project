#include "../include/hash.h"
#include <string.h>


/**
 * 功能: hash散列函数
 * 参数: @key
 * 返回: 散列结果
 **/
static unsigned int hashFunc(const void *key)
{
    unsigned int h = 5381;
    char *ptr = (char *)key;
    while(*ptr != '\0') {
        h = (h+(h<<5)) + (*ptr++);
    }
    return h;
}

/**
 * 默认的赋值函数
 * @param  key
 * @return     [description]
 */
void *hashDefaultSet(const void *key) {
    return strdup(key);
}
/**
 * 默认的key 释放函数
 * @param key
 */
void hashDefaultFree(void *key) {
    free(key);
}

/**
 * 默认的key比较函数
 * @param  key1 [description]
 * @param  key2 [description]
 * @return      [description]
 */
int hashDefaultCmp(const void *key1, const void *key2) {
    return strcmp(key1, key2);
}

HashTable * hashCreate(int capcity) {
    HashTable *ht = (HashTable *)malloc(sizeof(*ht));
    if (ht == NULL) {
        return NULL;
    }
    ht->capcity = capcity;
    ht->size = 0;
    ht->datas = (HashEntry **)calloc(capcity, sizeof(HashEntry*));

    return ht;
}


int hashInsert(HashTable *ht, const void *key, const void *value) {

    return 0;
}


int hashRemove(HashTable *ht, const void *key) {

    return 0;
}

int hashForEach(HashTable *ht, int (*foreach)(const HashEntry *entry, void *userptr), void *userptr) {

    return 0;
}

int hashGet(HashTable *ht, const void *key) {

}

/**
 * 销毁ht 所分配的空间
 * @param ht [description]
 */
void hashDestroy(HashTable *ht) {

}

/**
 * 清空数据，但是为HashTable 分配的空间
 * @param ht [description]
 */
void hashClear(HashTable *ht) {

}
