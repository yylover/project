#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "../include/hash.h"

/**
 * 1. 哈希表插入，要判断空间，如果空间达到一定的比例，要重新分配更大的空间
 * 2. 哈希表插入，如果原来有key, 则直接替换原来的值
 *
 */

/**
 * 功能: hash散列函数
 * 参数: @key
 * 返回: 散列结果
 **/
static unsigned int hashFunc(const void *key)
{
    unsigned int h = 5381;
    char *ptr = (char *)key;
    while (*ptr != '\0') {
        h = (h+(h<<5)) + (*ptr++);
    }
    return h;
}

/**
 * 获取大于n的最小的2^幂
 *
 * 初始化存储空间的时候是安装2的幂次方非配空间的
 * @param  n capacity
 * @return
 */
static unsigned int getNextPower(unsigned long size) {
    //溢出判断
    if (size >= LONG_MAX / 2) {
        return size;
    }

    unsigned long res = HASH_INIT_SIZE;
    while (res < size) {
        res <<= 1;
    }
    return res;
}

/**
 * 哈希表初始化
 * @param  ht      哈希表
 * @param  capacity 容量
 * @return
 */
static int hashInit(HashTable *ht, unsigned int capacity) {
    assert(ht);

    ht->capacity  = getNextPower(capacity);
    ht->size = 0; //重置个数

    ht->datas  = (HashEntry **)calloc(ht->capacity, sizeof(HashEntry*));
    if (!ht->datas) {
        return -1;
    }
    return 0;
}

/**
 * 哈希表插入一个entry节点
 *
 * 采用头插法
 * @param  ht    哈希表
 * @param  entry entry节点
 * @return       [description]
 */
static int hashInsert(HashTable *ht, HashEntry *entry) {
    assert(ht && entry);

    int index = hashFunc(entry->key) % ht->capacity;
    HashEntry *he = ht->datas[index];
    entry->next = he;
    ht->datas[index] = entry;
    ht->size++;

    return 0;
}

/**
 * 哈希表创建一个节点
 * @param  ht  HashTable
 * @param  key
 * @param  val
 * @return
 */
static HashEntry * hashCreateEntry(HashTable *ht, const void *key, const void *val) {

    HashEntry *he = (HashEntry *) calloc(1, sizeof(*he));
    if (he == NULL) {
        return NULL;
    }

    he->next = NULL;
    HASH_SET_KEY(ht, he, (void *)key);
    HASH_SET_VAL(ht, he, (void *)val);
    // he->key = ht->setKey(key);
    // he->value = ht->setVal(val);

    return he;
}

/**
 * 释放哈希表的一个节点
 * @param  ht
 * @param  he
 * @return
 */
static int hashFreeEntry(HashTable *ht, HashEntry *he) {
    HASH_FREE_KEY(ht, he);
    HASH_FREE_VAL(ht, he);

    he->next = NULL;
    free(he); //he 指向的空间也要释放
    he = NULL;
    ht->size--;

    return 0;
}

/**
 * 将哈希表的空间扩大两倍,并释放原来的空间
 *
 * 复用了原来的哈希表节点，只对datas重新分配空间
 * 哈希表扩容时，原来的需要重新插入
 * @param       ht 哈希表
 * @return     HashTable *
 */
static int hashResize(HashTable *ht) {
    assert(ht);

    int capacity = ht->capacity;
    HashEntry **datas = ht->datas;

    if (hashInit(ht, ht->capacity*2) != 0) {
        //内存分配失败
        ht->datas = datas;
        return -1;
    }

    //遍历ht元素插入到新的哈希表中
    int i = 0;
    HashEntry *t = NULL, *temp = NULL;
    for (i = 0; i < capacity; i++) {
        t = datas[i];
        while (t != NULL) {
            temp = t;
            t = t->next;
            hashInsert(ht, temp);
        }
    }

    //释放原来的空间
    if (datas) {
        free(datas);
    }

    return 0;
}

/**
 * 对每个HashEntry 执行删除
 * @param  entry
 * @param  userptr
 * @return
 */
int foreachDeleteEntry(const void *key, void *val, void *userptr) {
    HashTable *ht = (HashTable *)userptr;
    return hashRemove(ht, key);
}

/**
 * 默认的赋值函数
 * @param  key
 * @return     [description]
 */
void *hashDefaultSet(const void *key) {
    return strdup(key); //strdup 要free
}
/**
 * 默认的key 释放函数
 * @param key
 */
void hashDefaultFree(void *key) {
    if (key) {
        free(key);
    }
}

/**
 * 默认的key比较函数
 * @param  key1 [description]
 * @param  key2 [description]
 * @return      [description]
 */
int hashDefaultCmp(const void *key1, const void *key2) {
    return strcmp(key1, key2) == 0;
}

/**
 * 创建哈希表
 * @param  capacity [description]
 * @return         [description]
 */
HashTable * hashCreate(int capacity) {
    HashTable *ht = (HashTable *)malloc(sizeof(*ht));
    if (!ht) {
        return NULL;
    }

    if (hashInit(ht, capacity) != 0) {
        free(ht);
        ht = NULL; //指针指空
        return NULL;
    }

    HASH_SET_SETKEY(ht, hashDefaultSet);
    HASH_SET_SETVAL(ht, hashDefaultSet);
    HASH_SET_FREEKEY(ht, hashDefaultFree);
    HASH_SET_FREEVAL(ht, hashDefaultFree);
    HASH_SET_KEYCMP(ht, hashDefaultCmp);

    return ht;
}

/**
 * 插入元素
 * @param  ht    [description]
 * @param  key   [description]
 * @param  value [description]
 * @return       [description]
 */
int hashSet(HashTable *ht, const void *key, const void *value) {

    if ((ht->size / ht->capacity) >= HASH_RESIZE_RATIO) {
        if (hashResize(ht) != 0) {
            return -1;
        };
    }

    //查找原来是否有此元素
    int index = hashFunc(key) % ht->capacity;
    HashEntry *he = ht->datas[index];
    while (he) {
        if (HASH_CMP_KEYS(ht, he->key, key)) {
            HASH_FREE_VAL(ht, he);//** 要对原来的值进行释放
            HASH_SET_VAL(ht, he, (void *)value);
            return 0;
        }
        he = he->next;
    }

    if ((he = hashCreateEntry(ht, key, value)) == NULL) {
        return -1;
    }

    if (hashInsert(ht, he) != 0) {
        hashFreeEntry(ht, he);
        return -1;
    }

    return 0;
}

/**
 * 删除哈希表元素
 * @param  ht  哈希表
 * @param  key key
 * @return
 */
int hashRemove(HashTable *ht, const void *key) {
    assert(ht && key);

    HashEntry *pre = NULL, *ptr = NULL;
    int index = hashFunc(key) % ht->capacity;

    ptr = ht->datas[index];
    while (ptr) {
        if (HASH_CMP_KEYS(ht, ptr->key, key)) {
            break;
        }
        pre = ptr;
        ptr = ptr->next;
    }

    // printf("%d %s %s\n", index, (char *)ptr->key, (char *)ptr->value);
    if (ptr) {
        if (pre) {
            pre->next = ptr->next;
        } else {
            ht->datas[index] = ptr->next;
        }
        hashFreeEntry(ht, ptr);
        return 0;
    }

    return -1;
}

/**
 * 查找哈希表表元素
 *
 * 查找和删除都要有查找的过程
 * @param ht
 * @param key
 */
void* hashGet(HashTable *ht, const void *key) {
    int index = hashFunc(key) % ht->capacity;

    HashEntry *ptr = ht->datas[index];
    while (ptr) {
        if (HASH_CMP_KEYS(ht, ptr->key, key)) {
            return ptr->value;
        }
        ptr = ptr->next;
    }

    return NULL;
}


/**
 * 对哈希表的每个元素执行函数
 *
 * 函数设计并不好，不用实现这样的函数，HashEntry可以认为是内部的数据结构
 * @param  ht      哈希表吧
 * @param  foreach
 * @return         [description]
 */
int hashForEach(HashTable *ht, int (*foreach)(const void *key, void *val, void *userptr), void *userptr) {
    assert(ht && foreach);

    HashEntry *he = NULL, *next = NULL;
    for (int i = 0; i < ht->capacity; i++) {
        he = ht->datas[i];
        while (he) {
            next = he->next;
            if (foreach(he->key, he->value, userptr) != 0) {
                return -1;
            }
            //TODO 可能有bug,因为Foreach可能执行删除函数
            he = next;
        }
    }

    return 0;
}

/**
 * 清空数据，但是为HashTable 分配的空间
 * @param ht [description]
 */
void hashClear(HashTable *ht) {
    hashForEach(ht, foreachDeleteEntry, ht);
    memset(ht->datas, 0, sizeof(HashEntry *)*ht->capacity);
    // ht->size = 0;
}

/**
 * 销毁ht 所分配的空间,不释放ht
 * @param ht [description]
 */
void hashDestroy(HashTable *ht) {
    hashForEach(ht, foreachDeleteEntry, ht);
    free(ht->datas);

    ht->datas = NULL;
    ht->size = 0;
    ht->capacity = 0;

    ht->setKey = NULL;
    ht->setVal = NULL;
    ht->freeKey = NULL;
    ht->freeVal = NULL;
    ht->keyCmp = NULL;
}

/**
 * 释放哈希表
 * @param ht
 */
void hashFree(HashTable *ht) {
    hashDestroy(ht);
    free(ht);
    ht = NULL;
}

/**
 * 复制哈希表的节点
 * @param  key      [description]
 * @param  val      [description]
 * @param  userdata [description]
 * @return          [description]
 */
static int hashDupEach(const void *key, void *val, void *userdata) {
    HashTable *ht = (HashTable *) userdata;
    return hashSet(ht, key, val);
}


/**
 * 复制一个新的哈希表
 * @param  ht [description]
 * @return    [description]
 */
HashTable *hashDuplicate(HashTable *ht) {
    HashTable *htNew = hashCreate(ht->capacity);
    if (!ht) {
        return NULL;
    }

    HASH_SET_SETKEY(htNew, ht->setKey);
    HASH_SET_SETVAL(htNew, ht->setVal);
    HASH_SET_FREEKEY(htNew, ht->freeKey);
    HASH_SET_FREEVAL(htNew, ht->freeVal);
    HASH_SET_KEYCMP(htNew, ht->keyCmp);

    if (hashForEach(ht, hashDupEach, (void*)htNew) != 0) {
        hashFree(htNew);
        htNew = NULL;
    }
    return htNew;
}



void print_str(char *str) {
    while (*str != '\0') {
        printf("%c", *str);
        str++;
    }
    printf("\n");
}

#ifdef __HASH_MAIN_TEST_

int main() {
    char *str = "hello world";
    print_str(str);
    char *str2 = "502341152355";
    print_str(str2);

    char *str3 = (char *) malloc(10 *sizeof(char));
    strcpy(str3, "hello");
    print_str(str3);

    printf("%d\n", (int)str3);
    char *str4 =realloc(str3, 20);
    printf("%s\n", str4);
    printf("%s\n", str3);
    printf("%d\n", (int)str3);

    return 0;
}

#endif
