/*****************************************************************************
Copyright: 2017~2030 yangqiang personal
File name: adlist.h
Description: a generic doubly linked list implementation
Author: yangqiang
Version: 1.0
Date:
History:

双链接表结构和操作逻辑声明:
1. 空链表:head tail 都为NULL, length=0
2. free 指针用于释放value的值，不需要释放可以填写NULL
3. match 用于比较value的值，如果没有设置，直接使用== 比较

1. 疑问:函数指针？实现

*****************************************************************************/

#ifndef __ADLIST_H_
#define __ADLIST_H_

#define AL_START_HEAD 0
#define AL_START_TAIL 1

typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

typedef struct listIter {
    listNode *next;
    int direction;
} listIter;

typedef struct list {
    listNode *head;      //头结点
    listNode *tail;      //尾节点
    unsigned long length; //数据个数
    void *(*dup)(void *ptr);  //复制
    void (*free)(void *ptr); //释放value的值得，
    int (*match)(void *ptr1, void *ptr2); //比较
} list;

//宏实现的函数
#define listLength(l) ((l)->length)
#define listFirst(l) ((l)->head)
#define listLast(l) ((l)->tail)
#define listNodeNext(l) ((l)->next)
#define listNodePrev(l) ((l)->prev)
#define listNodeValue(l) ((l)->value)

#define listSetDupMethod(l, m) ((l)->dup = (m))
#define listSetFreeMethod(l, m) ((l)->free = (m))
#define listSetMatchMethod(l, m) ((l)->match = (m))

#define listGetDupMethod(l) ((l)->dup)
#define listGetFreeMethod(l) ((l)->free)
#define listGetMatchMethod(l) ((l)->match)

//函数原型prototypes
list *listCreate(void);
void listRelease(list *);
list *listDup(list *orgi);
list *listAddNodeHead(list *, void *value);
list *listAddNodeTail(list *, void *value);
list *listInsertNode(list *, listNode* old, void *value, int after);
void listDeleteNode(list *, listNode *node);
listIter *listGetIterator(list *, int);
listNode *listNext(listIter *);
void listReleaseIterator(listIter *);

listNode *listSearchKey(list *, void *);
listNode *listIndex(list *, int);
void listRewind(list *, listIter *);
void listRewindTail(list *, listIter *);
void listRotate(list *);

int add(int a, int b);

#endif
