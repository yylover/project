#ifndef __HASH_H__
#define __HASH_H__

//重新分配空间的大小比例
const int HASH_RESIZE_RATIO = 1; //重新分配空间的比例
const int HASH_INIT_SIZE = 32; //最小分配空间

//最什么没有给默认的set free 函数，因为不确定是否一定是可以用free释放的
#define HASH_SET_SETKEY(ht, func) (ht)->setKey = (func)
#define HASH_SET_SETVAL(ht, func) (ht)->setVal = (func)
#define HASH_SET_KEYCMP(ht, func) (ht)->keyCmp = (func)
#define HASH_SET_FREEKEY(ht, func) (ht)->freeKey = (func)
#define HASH_SET_FREEVAL(ht, func) (ht)->freeVal = (func)

#define HASH_SET_KEY(ht, he, _key_) do {\
    if ((ht)->setKey) {\
        (he)->key = (ht)->setKey(_key_);\
    } else {\
        (he)->key = (_key_);\
    }\
} while(0)

#define HASH_SET_VAL(ht, he, _val_) do {\
    if ((ht)->setVal) {\
        (he)->value = (ht)->setVal(_val_);\
    } else {\
        (he)->value = (_val_);\
    }\
} while(0)

#define HASH_FREE_KEY(ht, he) do {\
    if ((ht)->freeKey) {\
        (ht)->freeKey((he)->key);\
    } \
} while (0)

#define HASH_FREE_VAL(ht, he) do {\
    if ((ht)->freeVal) {\
        (ht)->freeVal((he)->value);\
    } \
} while (0)

#define HASH_CMP_KEYS(ht, key1, key2) \
    (ht)->keyCmp ? (ht)->keyCmp((key1), (key2)) : (key1) == (key2)


// hash 的节点
typedef struct hashEntry {
    void *key;
    void *value;
    struct hashEntry *next;
} HashEntry;

//hash 结构体
typedef struct hash {
    HashEntry **datas;
    unsigned int capcity; //
    unsigned int size;    //长度

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
int hashSet(HashTable *ht, const void *key, const void *value);
int hashRemove(HashTable *ht, const void *key);
int hashForEach(HashTable *ht, int (*foreach)(const HashEntry *entry, void *userptr), void *userptr);
void* hashGet(HashTable *ht, const void *key);
void hashClear(HashTable *ht);   //清空所有数据
void hashDestroy(HashTable *ht); //删除table
void hashFree(HashTable *ht);    //
HashTable *hashDuplicate(HashTable *ht);

HashIter *hashIterCreate(HashTable *ht); //创建遍历
int hashIterMoveNext(HashIter *iter);   //向后移动
int hashIterMovePrev(HashIter *iter);   //向前移动
int hashIterReset(HashIter *iter);      //重置位置
void hashIterFree(HashIter *iter);      //释放

//默认的key set 和free函数,默认都是作为字符串，free方式释放
void *hashDefaultSet(const void *key);
void hashDefaultFree(void *key);
int hashDefaultCmp(const void *key1, const void *key2);
#endif
