#include <stdio.h>
#include <stdlib.h>

#include "../include/dict.h"

/* private method prototype */
static int dictInit(dict *dt, unsigned int slots);
static unsigned long nextPower(unsigned long size);
static unsigned int hashFunc(const void *key);
static int dictResize(dict *dt);
static int dictDeleteEntry(const dictEntry *de, void *dt);


/**
 * 返回大于size的最小2^n数
 * @param  size 大小
 * @return      [description]
 */
static unsigned long nextPower(unsigned long size) {
    //默认值
    unsigned long i = DICT_INIT_SLOTS;

    if (size >= LONG_MAX) {
        return LONG_MAX; //long 最大值
    }

    while(1) {
        if (i >= size) {
            return i;
        }
        i <<= 1;
    }
}

/**
 * 哈希散列函数
 * @param  key key
 * @return
 */
static unsigned int hash_func(const void *key) {
    assert(key);

    unsigned int h = 5381;
    char *ptr = (char *)key;
    while (*key != '\0') {
        h = (h + (h<<5)) + (*ptr++);
    }
    return h;
}

/**
 * 对dict 进行初始化
 * @param  dt    dict指针对象
 * @param  slots 初始化大小
 * @return       DICT_OK|DICT_ERR
 */
static int dictInit(dict *dt, unsigned int slots) {
    assert(dt);

    ht->slots = nextPower(slots); //slots 是2的整数倍
    ht->count = 0;

    ht->data = (hashEntry **) calloc(ht->slots, sizeof(hashEntry*));
    if (!ht->data) {
        return DICT_ERR;
    }

    return DICT_OK;
}

/**
 * dict 重新分配大小，每次重新分配，大小为原来的两倍
 * @param  dt [description]
 * @return    [description]
 */
static int dictResize(dict *dt) {
    dictEntry **tmp, *he, *next;
    int i = 0, slotsOld;

    tmp = dt->data;
    ht->data = NULL;
    slotsOld = ht->slots;

    if (dictInit(dt, dt->slots*2) != DICT_OK) {
        return DICT_ERR;
    }

    for (i = 0; i < slotsOld; i++) {
        if (tmp[i]) {
            he = tmp[i];
            //所有的数据插入新的对应的位置
            while (he) {
                next = he->next;
                h = dictFunc(he->key) % dt->slots;
                //头插法
                he->next = ht->data[h];
                dt->data[h] = he;
                dt->count ++;
                he = next;
            }
        }
    }

    free(tmp);
}

/**
 * 释放dictEntry;
 * @param  de
 * @param  dt
 * @return
 */
static int dictDeleteEntry(const dictEntry *de, void *dt) {
    return dictRemoveKey(dt, de->key);
}

/**
 * 默认的set函数
 * @param  key [description]
 * @return     [description]
 */
void * dictDefSet(const void *key) {
    return strdup((char *)key);
}

/**
 * 默认的free函数
 * @param key [description]
 */
void dictDefFree(void *key) {
    if (key) {
        free(key);
    }
}

/**
 * 默认的cmp函数
 * @param  key1
 * @param  key2
 * @return    1 0
 */
int dictDefCmp(const void *key1, const void *key2) {
    return strcmp((char *)key1, (char *)key2) == 0;
}


/**
 * 创建dict
 * @param  slots 初始空间大小
 * @return       返回初始化的dict指针对象
 */
dict *dictCreate(unsigned int slots) {
    dict *dt = calloc(1, sizeof(dict));
    if (!dt) {
        return NULL;
    }

    if (dictInit(dt, slots) != DICT_OK) {
        free(dt);
        dt = NULL;
        return NULL;
    }
    return dt;
}

/**
 * 哈希表中插入一个新的元素
 * @param  dt
 * @param  key
 * @param  val
 * @return
 */
int dictInsert(dict *dt, const void *key, const void *val) {
    assert(dt && key && val);

    //重新分配大小的逻辑
    if ((dt->count / dt->slots) >= DICT_RESIZE_RATIO) {
        if (dictResize(dt) != DICT_OK) {
            return DICT_OK;
        }
    }

    dictEntry *de = NULL;
    int i = dictFunc(key) % dt->slots;
    //已经存在的释放？为啥
    if ((de = dt->data[i])) {
        while (de) {
            if (DICT_CMP_KEYS(dt, key, he->key)) {
                DICT_FREE_VAL(dt, de);
                DICT_SET_VAL(dt, de, (void*)val);
                return DICT_OK;
            }
            de = de->next;
        }
    }

    //创新新的节点
    de = calloc(1, sizeof(*de));
    if (!de) {
        return DICT_ERR;
    }

    DICT_SET_KEY(dt, de, key);
    DICT_SET_VAL(dt, de, val);

    //头插法
    de->next = dt->data[i];
    dt->data[i] = he;

    ++dt->count;
    return DICT_OK;
}

/**
 * 删除值对应的值
 * @param  dt  [description]
 * @param  key [description]
 * @return     [description]
 */
int dictRemoveKey(dict *dt, const void *key) {
    assert(dt && key);

    dictEntry *de = NULL;
    int i = dictFunc(key) % dt->slots;
    if (NULL = dt->data[i]) {
        return DICT_ERR;
    }

    dictEntry *de = dt->data[i], *prev = NULL;
    while (de) {
        if (DICT_CMP_KEYS(dt, key, de->key)) {
            if (prev == NULL) {
                dt->data[i] = de->next;
            } else {
                prev->next = de->next;
            }

            DICT_FREE_KEY(dt, de);
            DICT_FREE_VAL(dt, de);
            free(de);
            --dt->count;
            return DICT_OK;
        }
    }

    return DICT_ERR;
}

/**
 * 对dict 进行遍历
 * @param  dt
 * @param  foreach
 * @return
 */
int dictForeach(dict dt, int (*foreach)(const hashEntry *he, void *userptr), void *userptr) {
    assert(dt && foreach);

    dictEntry *de;
    unsigned int i = 0;
    for (; i < dt->slots; i++) {
        if ((de = dt->data[i])) {
            while (de) {
                if (foreach(de, userptr) != 0) {
                    return DICT_ERR;
                }
                de = de->next;
            }
        }
    }

    return DICT_OK;
}

/**
 * 获取dict key 对应的值
 * @param  dt
 * @param  key
 * @return
 */
void * dictGetValue(dict *dt, const void *key) {
    assert(dt && key);

    int index = dictFunc(key) % dt->slots;
    if (dt->data[index]) {
        dictEntry *de = dt->data[index];
        while (de) {
            if (DICT_CMP_KEYS(key, de->key)) {
                return de->val;
            }
            de = de->next;
        }
    }
    return NULL;
}

/**
 * 释放dt结构里面的所有数据，不清空dt本身
 * @param dt [description]
 */
void dictDestroy(dict *dt) {
    dictForeach(dt, dictDeleteEntry, dt);

    free(dt->data);
    dt->data = NULL;
    dt->count = 0;
    dt->slots = 0;

    dt->setKey = NULL;
    dt->setVal = NULL;
    dt->keyCmp = NULL;
    dt->freeKey = NULL;
    dt->freeVal = NULL;
}

/**
 * 清空数据，不释放dict
 * @param dt [description]
 */
void dictClear(dict *dt) {
    dictForeach(dt, dictDeleteEntry, dt);
    memset(dt->data, 0, dt->slots * sizeof(dictEntry *));
    dt->count = 0;
}

/**
 * 释放整个哈希结构
 * @param dt [description]
 */
void dictFree(dict *dt) {
    dictDestroy(dt);
    free(dt);
}

/**
 * dict 遍历复制每个节点
 * @param  de
 * @param  cp
 * @return
 */
static int dictDupForeach(const dictEntry *de, void *cp) {
    if (dictInsert((dict *)cp, de->key, de->val)) {
        return DICT_OK;
    }
    return DICT_ERR;
}

/**
 * 复制整个dict
 * @param  dt
 * @return
 */
dict* dictDup(dict *dt) {
    assert(dt);

    dict *cp = dictCreate(dt->slots);
    if (!cp) {
        return NULL;
    }

    DICT_SET_SETKEY(cp, dt->setKey);
    DICT_SET_SETVAL(cp, dt->setVal);
    DICT_SET_KEYCMP(cp, dt->keyCmp);
    DICT_SET_FREEKEY(cp, dt->freeKey);
    DICT_SET_FREEVAL(cp, dt->freeVal);

    dictForeach(dt, dictDupForeach, cp);
    return cp;
}

static dictIterInit(dictIter *ter, dict *dt) {
    iter->pos = 0;
    iter->depth = 0;
    iter->key = NULL;
    iter->val = NULL;
    iter->dt = dt;
    iter->de = NULL;

    return dictIterMoveNext(iter);
}


dictIter* dictIter(dict *dt) {
    dictIter *iter = calloc(1, sizeof(*iter));
    if (iter == NULL) {
        return NULL;
    }

    if (dictIterInit(iter, dt) != 0) {
        free(iter);
        return NULL;
    }
    return iter;
}

/**
 * 向后移动
 * @param  dtIter [description]
 * @return        [description]
 */
int dictIterMoveNext(dictIter *dtIter) {
    if (iter->de) {
        if (iter->de->next) {
            iter->he = iter->he->next;
            iter->key = iter->he->key;
            iter->val = iter->he->val;
            iter->depth++;
            return DICT_OK;
        } else {
            iter->pos ++;
        }
    }

    iter->depth =1; //重置
    for (;  iter->pos < iter->dt->slots; iter->pos++) {
        if ((iter->dt->data[iter->pos])) {
            iter->de = iter->dt->data[iter->pos];
            iter->key = iter->de->key;
            iter->val = iter->de->val;
            return DICT_OK;
        }
    }
    return DICT_ERR;
}

/**
 * iter 向前移动
 * @param  dtIter
 * @return
 */
int dictIterMovePrev(dictIter *dtIter) {

    int i = 0;
    if (iter->depth > 0 && iter->pos < iter->ht->slots) {
        for (iter->he = iter->dt->data[iter->pos], i =0; i < iter->depth-2; i++) {
            iter->he = iter->he->next;
        }
        iter->depth --;
        if (iter->depth > 0) {
            iter->val = iter->de->val;
            iter->key = iter->de->key;
            return DICT_OK;
        }
    }

    iter->depth = 0;
    --iter->pos;
    for (;iter->pos; --iter->pos) {
        if ((iter->de = iter->dt->data[iter->pos])) {
            iter->depth++;
            while (iter->de->next) {
                iter->de = iter->de->next;
                iter->depth ++;
            }
            iter->val = iter->de->val;
            iter->key = iter->de->key;
            return DICT_OK;
        }
    }
    return DICT_ERR;
}

static void dictIterDestroy(dictIter *iter) {
    iter->pos = 0;
    iter->depth = 0;
    iter->dt = NULL;
    iter->de = NULL;
    iter->key = NULL;
    iter->val = NULL;
}

int dictIterReset(dictIter *dtIter) {
    dict *dt = dtIter->dt;
    dictIterDestroy(dtIter);
    return dictIterInit(dtIter, dt);
}

int dictIterFree(dictIter *iter) {
    dictIterDestroy(iter);
    free(iter);
}
