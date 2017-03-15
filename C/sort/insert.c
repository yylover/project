
#include <stdio.h>
/**

# 内排序
## 插入排序
    * 直接插入排序
    * 希尔排序

## 选择排序
    * 简单选择排序
    * 堆排序

## 交换排序
    * 冒泡排序
    * 快速排序

## 归并排序
## 基数排序


### 插入排序
将一个记录插入到已经排序的有序表中，从而得到一个有序的，记录数+1的有序表。

### 简单选择排序
一组数中，选择最小的一个跟第一个交换





 */


void swap_array(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

/**
 * 插入排序
 * @param  a   数组
 * @param  num 数组长度
 * @return     0 成功，-1 失败
 */
void insert_sort(int a[], int num) {
    for (size_t i = 1; i < num; i++) {
        for (size_t j = i; j > 0; j--) {
            if (a[j] <= a[j-1]) {
                swap_array(a, j-1, j);
            } else {
                break;
            }
        }
    }
}

/**
 * 希尔排序
 *
 * 缩减增量排序，实质是分组插入排序
 * 非稳定排序
 * @param a
 * @param num
 */
void shell_sort(int a[], int num) {
    int step = num / 2;
    while (step != 0) {
        for (size_t i = step; i < num; i++) {
            int temp = a[i], j = 0; //必须使用temp,因为a[i]会被覆盖
            for (j = i-step; j >= 0 && temp < a[j]; j-=step) {
                a[j+step] = a[j];
            }
            a[j+step] = temp;
        }

        step /= 2;
    }
}

/**
 * 简单选择排序
 *
 * 思路：选择最小的一个跟第一个交换
 * @param a   [description]
 * @param num [description]
 */
void simple_selecion_sort(int a[], int num) {

    for (size_t i = 0; i < num-1; i++) {
        int min = a[i], minIndex = i;
        for (size_t j = i+1; j < num; j++) {
            if (a[j] < min) {
                min = a[j];
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swap_array(a, i, minIndex);
        }
    }
}

/**
 * 冒泡排序
 * 冒泡排序属于交换排序，相邻两个如果第二个比第一个大，那么交换他们
 * @param a
 * @param num
 */
void bubble_sort(int a[], int num) {
    for (size_t i = num-1; i > 0; i--) {
        for (size_t j = 0; j < i; j++) {
            if (a[j] > a[j+1]) {
                swap_array(a, j, j+1);
            }
        }
    }
}


//将i和j之间的元素进行快排
void qsort(int a[], int i, int j) {
    if (i == j) {
        return ;
    }

    int temp = a[i];
    int m = i, n = j;

    while (m < n) {

        while (a[n] > temp && m < n) {
            n--;
        }
        swap_array(a, m, n);

        while (a[m] < temp && m < n) {
            m++;
        }
        swap_array(a, m, n);
    }

    if (m -i > 1) {
        qsort(a, i, m-1);
    }

    if (j-m > 1) {
        qsort(a, m+1, j);
    }
}
/**
 * 快速排序
 *
 * 基本思想：
 * 1. 选择一个基准元素，通常选择第一个或最后一个
 * 2. 一趟排序，将记录分成两部分，比基值小的在其左侧，比基值大的在右侧
 * 3. 对两侧元素递归实现
 * @param a
 * @param num
 */
void q_sort(int a[], int num) {
    qsort(a, 0, num-1);
}


//构造堆
void build_heap(int a[], int num, int index) {
    int smallestIndex = index;
    int temp;

    while (smallestIndex < num) {
        temp = 2 * index + 1;
        if (temp < num && a[temp] < a[smallestIndex]) {
            smallestIndex = temp;
        }

        temp = 2 * index + 2;
        if (temp < num && a[temp] < a[smallestIndex]) {
            smallestIndex = temp;
        }

        if (smallestIndex != index) {
            swap_array(a, index, smallestIndex);
            index = smallestIndex;
        } else { //退出
            return ;
        }
    }

}


/**
 * 堆排序
 * @param a
 * @param num
 */
void heap_sort(int a[], int num) {
    //构造堆
    for (size_t i = num/2 -1; i < num; i--){
        build_heap(a, num, i);
    }

    int index = num-1;
    while (index > 0) {
        swap_array(a, index, 0);
        build_heap(a, index, 0);
        index--;
    }
}


void display_array(int a[], int num) {
    for (int i = 0; i < num; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[] = {3, 2, 1, 4, 5, 11, 22, 15, 7, 9, 8};
    heap_sort(a, 11);
    display_array(a, 11);

    int b[] = {1};
    heap_sort(b, 1);
    display_array(b, 1);

    int c[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    heap_sort(c, 10);
    display_array(c, 10);

    return 0;
}
