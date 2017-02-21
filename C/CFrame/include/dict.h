//哈希值相同的形成一个链表

#ifndef __DICT_H__
#define __DICT_H__

#define DICT_OK  0
#define DICT_ERR -1

#define DICT_NOTUSED(V) ((void)V)

#define DICT_INIT_SLOTS 32
#define DICT_RESIZE_RATIO 1 // ht->count /ht->slots

#define DICT_SET_KEYCMP(dt, func) (dt)->keyCmp = (func)
#define DICT_SET_SETKEY(dt, func) (dt)->setKey = (func)
#define DICT_SET_SETVAL(dt, func) (dt)->setVal = (func)
#define DICT_SET_FREEKEY(dt, func) (dt)->freeKey = (func)
#define DICT_SET_FREEVAL(dt, func) (dt)->freeVal = (func)

#define DICT_SET_KEY(dt, entry, _key_) do{\
    if ((dt)->setKey) {\
        (entry)->key = (dt)->setKey(_key_);\
    } else {\
        (entry)->key = (_key_);\
    }\
} while(0)

#define DICT_SET_VAL(dt, entry, _val_) do{\
    if ((dt)->setVal) {\
        (entry)->value = (dt)->setVal(_val_);\
    } else {\
        (entry)->value = (_val_);\
    }\
} while(0)

#define DICT_FREE_KEY(dt, entry) do {\
    if ((dt)->freeKey) {\
        (dt)->freeKey((entry)->key);\
    }\
} while(0)

#define DICT_FREE_VAL(dt, entry) do {\
    if ((dt)->freeVal) {\
        (dt)->freeVal((entry)->value);\
    }\
} while(0)

#define DICT_CMP_KEYS(ht, key1, key2) \
    ((ht)->keyCmp) ? (ht)->keyCmp((key1), (key2)) : (key1)==(key2)\



typedef dictEntry {
    void *key;
    void *value;
    struct dictEntry *next;
} dictEntry;

typedef struct dict {
    unsigned int slots; //number of slots
    unsigned int count; //number of key/vale paris used
    dictEntry **data;   //table

    int (*keyCmp)(const void *, const void *);
    void* (*setkey)(const void *);
    void* (setVal)(const void *);
    void (*freeKey)(void *);
    void (*freeVal)(void *);
} dict;

typedef struct dictIter {
    dictEntry *de;
    dict *dt;

    int pos;   //在数组中位置
    int depth; //在链表中位置
    void *key;
    void *val;

} dictIter;

dict *dictCreate(unsigned int slots);
int dictInsert(dict *dt, const void *key, const void *val);
int dictRemoveKey(dict *dt, const void *key);
int dictForeach(dict dt, int (*foreach)(const hashEntry *he, void *userptr), void *userptr);
void * dictGetValue(dict *dt, const void *key);
void dictDestroy(dict *dt);
void dictClear(dict *dt);
void dictFree(dict *dt);
dict* dictDup(dict *dt);
dictIter* dictIter(dict *dt);
int dictIterMoveNext(dictIter *dtIter);
int dictIterMovePrev(dictIter *dtIter);
int dictIterReset(dictIter *dtIter);
int dictIterFree(dictIter *iter);
void * dictDefSet(const void *key);
void dictDefFree(void *key);
int dictDefCmp(const void *key1, const void *key2);

#endif
