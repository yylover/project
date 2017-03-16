#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/**
 * 替换空格,假设原来的空间是够用的
 *
 * O(n) 算法，先遍历一遍，计算空格的个数
 * @param string [description]
 * @param length [description]
 */
void replaceBaack(char string[], int length) {
    int num = 0;
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ') {
            num++;
        }
    }

    int newLen = length + 2*num;
    int pre = length-1, behind = newLen-1;
    while (pre < behind) {
        if (string[pre] == ' ') {
            string[behind--] = '0';
            string[behind--] = '2';
            string[behind--] = '%';
        } else {
            string[behind] = string[pre--];
        }
    }

}

int main() {
    char str[30];
    char string[] = "we are happy";
    memset(str, 0, 30);
    memcpy(str, "we are happy", strlen(string));
    printf("%s %lu\n", str, strlen(str));
    replaceBaack(str, strlen(str));
    printf("%s %lu\n", str, strlen(str));

}
