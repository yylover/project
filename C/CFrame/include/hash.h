#ifndef __HASH_H__
#define __HASH_H__

// hash 的节点
typedef struct hashEntry {
    void *key;
    void *value;
    struct hashEntry *next;
} HashEntry;

//hash 结构体
typedef struct hash {
    HashEntry **datas;
    int capcity; //
    int size;    //长度

    int (*keyCmp) (const void *, const void *);
    void *(*setKey) (const void *);
    void *(*setVal) (const void *);
    void (*freeKey) (void *);
    void (*freeVal) (void *);
} HashTable;

// 遍历并不按顺序实现
typedef struct hashIter {
    HashEntry *ptr; //指针，
    int pos;        //datas数组位置
    int depth;      //链表位置

    // void *key;
    // void *val;
} HashIter;

HashTable * hashCreate(int capcity);
int hashInsert(HashTable *ht, const void *key, const void *value);
int hashRemove(HashTable *ht, const void *key);
int hashForEach(HashTable *ht, int (*foreach)(const HashEntry *entry, void *userptr), void *userptr);
int hashGet(HashTable *ht, const void *key);
void hashDestroy(HashTable *ht); //删除table
void hashClear(HashTable *ht); //清空所有数据

HashIter *hashIterCreate(HashTable *ht); //创建遍历
int hashIterMoveNext(HashIter *iter);   //向后移动
int hashIterMovePrev(HashIter *iter);   //向前移动
int hashIterReset(HashIter *iter);      //重置位置
void hashIterFree(HashIter *iter);      //释放

//默认的key set 和free函数
void *hashDefaultSet(const void *key);
void hashDefaultFree(void *key);
int hashDefaultCmp(const void *key1, const void *key2);
#endif
