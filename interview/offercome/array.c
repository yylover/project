#include <stdio.h>
#include <stdlib.h>
/**
 * 1. 二维数据参数传递，不能把第二维或更高的维省略
 *  1) void Func(int array[3][10]);
 *  2) void Func(int array[ ][10]);
 *  2) void Func(int (*array)[10]); 等同于2
 *  2)
 *
 *  void Func（int *array[10]);相当于声明一个int* 数组
 */



/**
 * 二维数组查找
 *
 * 切入的位置很重要
 * @param  num [description]
 * @return     [description]
 */
int findValue(int (*num)[4], int row, int column, int number) {
    if (row == 0 || column == 0) {
        return 0;
    }

    int i = 0, j = column-1;
    while (i < row && j >= 0) {
        printf("%d\n", num[i][j]);
        if (num[i][j] == number) {
            return number;
        } else if (num[i][j] > number) {
            j--;
        } else {
            i++;
        }
    }

    return 0;
}


int main() {
    int num[3][4] = {
        {1, 3, 5, 7},
        {2, 4, 7, 9},
        {3, 6, 8, 11}
    };
    int d = findValue(num, 3, 4, 8);

    printf("%d\n", d);

    return 0;
}
