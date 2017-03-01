
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * malloc memset 初始化
 * 两层循环得到答案时，直接return , 一个break;跳不出循环。
 * index1 index 步长表示的含义，相等时，表示一个字符。
 */

bool isPalindromicString(char *s, int index1, int index2) {
    if (index2 < index1 || index2 > strlen(s)) {
        return -1;
    }

    if (index2 - index1 == 0) {
        return true;
    }
    char *p1 = s + index1;
    char *p2 = s + index2;
    while (p1 < p2) {
        if (*p1 != *p2) {
            return false;
        }
        p1 ++;
        p2 --;
    }
    return true;
}

char* longestPalindrome(char* s) {
    if (s == NULL || strlen(s) == 0) {
        return NULL;
    }

    int i = 0, j = 0;
    int strLen = strlen(s);


    int maxLen = 0;
    int index1 = 0; // 索引位置
    int len = 0;
    char *res = NULL;

    int step = strLen -1;
    while(step > 0) {
        for (i = 0; i+step < strLen; i++) {
            if (isPalindromicString(s, i, i+step)) {
                // printf("%d\n", step);
                res = malloc((step+2) * sizeof(char));
                memset(res, 0, step+2);
                strncpy(res, s+i, step+1);
                return res;
            }
        }
        step --;
    }

    // printf("%d\n", step);
    if (step == 0) {
        res = malloc(2 * sizeof(char));
        strncpy(res, s, step+1);
    }
    return res;

}
