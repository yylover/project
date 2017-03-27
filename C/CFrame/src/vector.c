#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vector.h"

/**
 * Void * 拷贝，复制，获取
 */

/**
 * 对vectro进行扩展，容量是原来的两倍大小
 * calloc 原值和返回值是否相同?
 * @param  v 要扩容的vector
 * @return   -1 | 0
 */
static int vectorResize(vector *v) {
    void *temp = realloc(v->data, v->slots*2 *v->sizeElem);
    if (temp == NULL) {
        return -1;
    }

    v->data = temp;
    v->slots *= 2;
    return 0;
}

vector *vectorCreate(unsigned int slots, unsigned int sizeElem) {
    if (slots <= 0) {
        slots = VECTOR_MIN_SIZE;
    }

    vector *v = NULL;
    if (NULL == (v = malloc(sizeof(vector)))) {
        return NULL;
    }

    if (NULL == (v->data = calloc(slots, sizeElem))) {
        free(v);
        return NULL;
    }
    v->slots = slots;
    v->sizeElem = sizeElem;
    v->count = 0;

    return v;
}

void vectorFree(vector *v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

/**
 * vecotr 设置index数据为elem
 * @param  v     [description]
 * @param  index [description]
 * @param  elem  [description]
 * @return       [description]
 */
int vectorSetAt(vector *v, unsigned int index, void *elem) {
    while (index >= v->slots) { //扩容
        if (vectorResize(v) == -1) {
            return -1;
        }
    }

    memcpy(v->data+index*v->sizeElem, elem, v->sizeElem);
    if (index >= v->count) {
        //避免之前有数据而产生脏数据
        memset(v->data + v->count*v->sizeElem, 0, (index-v->count)*v->sizeElem);
        v->count = index +1;
    }


    return 0;
}

void *vectorGetAt(vector *v, unsigned int index) {
    if (index > v->slots-1) {
        return NULL;
    }

    return v->data + (v->sizeElem * index);
}

int vectorPush(vector *v, void *elem) {
    if (v->count == v->slots) {
        if (vectorResize(v) != 0) {
            return -1;
        }
    }

    return vectorSetAt(v, v->count, elem);
}

/**
 * 获取栈顶元素并pop
 *
 * @param  v [description]
 * @return   [description]
 */
void *vectorPop(vector *v) {
    if (v->count == 0) {
        return NULL;
    }

    v->count--;
    return v->data + v->sizeElem*v->count; //没有置空
}

/**
 * 获取栈顶元素不pop
 * @param  v vector
 * @return   栈顶元素
 */
void *vectorTop(vector *v) {
    return vectorGetAt(v, v->count-1);
}

/**
 * 对vector所有元素进行排序
 * @param  v   [description]
 * @param  cmp [description]
 * @return     [description]
 */
int vectorSort(vector *v, vectorCmp cmp) {
    if (v->count == 0) {
        return -1;
    }
    qsort(v->data, v->count, v->sizeElem, cmp);
    return 0;
}

int vectorEach(vector *v, vectorEachFunc func, void *data) {
    if (func == NULL || v->count == 0) {
        return -1;
    }

    int i = 0;
    while (i < v->count) {
        void *elem = vectorGetAt(v, i);
        if (func(elem, data) == -1) {
            return -1;
        }
        i++;
    }
    return 0;
}

// int main(int argc, char *argv[]) {
//
// }
