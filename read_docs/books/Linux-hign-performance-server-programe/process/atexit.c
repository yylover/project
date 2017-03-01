#include <stdio.h>
#include <stdlib.h>

static void myexit1(void), myexit2(void);

/**
 * atexit()终止处理程序的处理应该是类似栈的结构
 * argv存储所有的参数
 * evnp 存储所有的环境变量
 */

int main(int argc, char *argv[], char *envp[]) {
    if (atexit(myexit2) != 0) {
        printf("%s\n", "can not register myexit2");
        return 0;
    }

    if (atexit(myexit1) != 0) {
        printf("%s\n", "can not register myexit2");
        return 0;
    }

    if (atexit(myexit1) != 0) {
        printf("%s\n", "can not register myexit2");
        return 0;
    }

    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);

    for (int i=0; envp[i]!= NULL;i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}

static void myexit1(void) {
    printf("%s\n", "first exit handler\n");
}

static void myexit2(void) {
    printf("%s\n", "second exit handler\n");
}
