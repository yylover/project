/*****************************************************************************
Copyright: 2017~2030 yangqiang personal
File name: vector.h
Description: a generic doubly linked list implementation
Author: yangqiang
Version: 1.0
Date:
History:

vector结构和操作逻辑声明:
1. 在一整片(size*slots)连续的内存中，模拟出数组的行为。
2. vecotr与普通数组的区别是，vector容量不足时，可以动态的扩充容量。


*****************************************************************************/

#ifndef __VECTOR_H_
#define __VECTOR_H_

#define VECTOR_MIN_SIZE 16

typedef struct vector {
    unsigned int slots; //槽位容量
    unsigned int count; //已经使用总数
    unsigned int sizeElem; //元素大小
    void *data; //数据数组
} vector;

typedef int (*vectorCmp)(const void *, const void *);
typedef int (*vectorEachFunc)(void *, void *);

vector *vectorCreate(unsigned int slots, unsigned int sizeElem);
void vectorFree(vector *v);
int vectorSetAt(vector *v, unsigned int index, void *elem);
void *vectorGetAt(vector *v, unsigned int index);
int vectorPush(vector *v, void *elem);
void *vectorPop(vector *v);
void *vectorTop(vector *v);
int vectorSort(vector *v, vectorCmp cmp);
int vectorEach(vector *v, vectorEachFunc func, void *data);

#endif
