
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/adlist.h"


/**
 * 创建空链表
 *
 * 空链表的头指针和尾指针都是NULL
 * TODO malloc 是否需要初始化
 * @return  链表指针
 */
list *listCreate(void) {
    list *adlist = NULL;
    if ((adlist = malloc(sizeof(list))) == NULL) {
        return NULL;
    }

    adlist->length = 0;
    adlist->dup = NULL;
    adlist->free = NULL;
    adlist->match = NULL;
    adlist->head = NULL;
    adlist->tail = NULL;
    return adlist;
}

/**
 * 释放链表
 * @param adlist 要释放的链表
 */
void listRelease(list *adlist) {
    listNode *node = listFirst(adlist);

    while (NULL != node) {
        listNode *temp = node;
        node = node->next;

        temp->prev = NULL;
        temp->next = NULL;
        if (adlist->free) {
            adlist->free(temp->value);
        }
        free(temp);
    }

    free(adlist);
}

/**
 * 复制整个双链表
 * @param  orgi 待复制的双链表
 *  注意复制要判断dup 函数，如果没有设置，采用值复制
 * @return
 */
list *listDup(list *orgi) {
    list *adlist = NULL;
    if (NULL == (adlist= listCreate())) {
        return NULL;
    }
    adlist->match = orgi->match;
    adlist->free = orgi->free;
    adlist->dup = orgi->dup;

    listNode *node = orgi->head;
    while (node) {
        void *value;
        if (adlist->dup) {
            value = adlist->dup(node->value);
            if (value == NULL) {
                listRelease(adlist);
                return NULL;
            }
        } else {
            value = node->value;
        }

        if (listAddNodeTail(adlist, node->value) == NULL) {
            listRelease(adlist);
            return NULL;
        }
        node = node->next;
    }
    return adlist;
}

/**
 * 双链表头部添加节点
 * @param  adlist 双链表
 * @param  value  值指针
 * @return        链表指针
 */
list *listAddNodeHead(list *adlist, void *value) {
    listNode *node = NULL;
    if (NULL == (node = malloc(sizeof(listNode)))) {
        return NULL;
    }

    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    if (adlist->length == 0) {
        adlist->head = node;
        adlist->tail = node;
    } else {
        node->next = adlist->head;
        adlist->head->prev = node;
        adlist->head = node;
    }
    adlist->length++;

    return adlist;
}

/**
 * 在双链表的尾部添加节点
 * @param  adlist 双链表
 * @param  value  值指针
 * @return        链表指针
 */
list *listAddNodeTail(list *adlist, void *value) {
    listNode *node = NULL;
    if (NULL == (node = malloc(sizeof(listNode)))) {
        return NULL;
    }

    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    if (adlist->length == 0) {
        adlist->head = node;
        adlist->tail = node;
    } else {
        node->prev = adlist->tail;
        adlist->tail->next = node;
        adlist->tail = node;
    }

    adlist->length++;
    return adlist;
}

/**
 * 添加节点
 * @param  adlist 链表指针
 * @param  old    给定节点
 * @param  value  值
 * @param  after  1 在后面添加， 0 在前面添加
 * @return        指针
 */
list *listInsertNode(list *adlist, listNode* old, void *value, int after) {
    listNode *node = NULL;
    if (NULL == (node = malloc(sizeof(listNode)))) {
        return NULL;
    }

    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    if (after) {
        if (adlist->tail == old) {
            old->next = node;
            node->prev = old;
            adlist->tail = node;
        } else {
            node->next = old->next;
            old->next->prev = node;
            node->prev = old;
            old->next = node;
        }
    } else {
        if (adlist->head == old) {
            node->next = old;
            old->prev = node;
            adlist->head = node;
        } else {
            node->next = old;
            node->prev = old->prev;
            old->prev->next = old;
            old->prev = node;
        }
    }

    adlist->length ++;
    return adlist;
}

/**
 * 删除节点
 * @param adlist 双链表
 * @param node   要删除的节点
 */
void listDeleteNode(list *adlist, listNode *node) {
    if (adlist->head == node && adlist->tail == node) {
        adlist->head = NULL;
        adlist->tail = NULL;
    } else if (adlist->head == node) {
        adlist->head = node->next;
        node->next->prev = NULL;
    } else if (adlist->tail == node) {
        adlist->tail = node->prev;
        node->prev->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    adlist->length--;
    if (adlist->free) {
        adlist->free(node->value);
    }
    free(node);
}

/**
 * 检索值对应的节点
 * @param  adlist 双链表
 * @param  value  值指针
 * @return
 */
listNode *listSearchKey(list *adlist, void *value) {
    listNode *node = adlist->head;
    while (NULL != node) {
        if (adlist->match) {
            if (adlist->match(value, node->value)) {
                return node;
            }
        } else {
            if (value == node->value) {
                return node;
            }
        }

        node = node->next;
    }
    return NULL;
}

/**
 * 索取索引位置对应的节点
 * @param  adlist 双链表指针
 * @param  index  索引,index 可以小于0，小于0从后计数
 * @return
 */
listNode *listIndex(list *adlist, int index) {
    listNode * node = NULL;

    if (index < 0) {
        node = adlist->tail;
        index = (-index)-1;
        while (node && index--) {
            node = node->prev;
        }
    } else {
        node = adlist->head;
        while(node && index--) {
            node = node->next;
        }
    }
    return node;
}

/**
 * 双链表反转操作
 * @param adlist [description]
 */
void listRotate(list *adlist) {
    listNode *next = NULL, *prev = NULL;
    listNode *node = adlist->tail;
    adlist->tail = adlist->head;
    adlist->head = node;

    while (node) {
        prev = node->prev;
        node->next = prev;
        node->prev = next;
        next = node;
        node = prev;
    }
}

/**
 * 迭代器
 * @param  [name] [description]
 * @return        [description]
 */
listIter *listGetIterator(list *adlist, int direction) {
    listIter *iter = NULL;
    if (NULL == (iter == malloc(sizeof(listIter)))) {
        return NULL;
    }

    iter->direction = direction;
    if (direction == AL_START_HEAD) {
        iter->next = adlist->head;
    } else {
        iter->next = adlist->tail;
    }

    return iter;
}

listNode *listNext(listIter *iter ) {
    listNode *current = iter->next;

    if (current != NULL) {
        if (iter->direction == AL_START_HEAD) {
            iter->next = current->next;
        } else {
            iter->prev = current->prev;
        }
    }

    return current;
}

void listReleaseIterator(listIter *iter) {
    free(iter);
}

void listRewind(list *adlist, listIter *iter) {
    iter->next = adlist->head;
    iter->direction = AL_START_HEAD;
}
void listRewindTail(list *adlist, listIter *iter) {
    iter->next = adlist->tail;
    iter->direction = AL_START_TAIL;
}

// int main(int argc, char *argv[]) {
//     int c = add(3, 5);
//     // printf("%d\n", c);
//     listCreate();
//
//     return 0;
// }
