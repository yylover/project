#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#define MAX_DUMP_STACK_DEPTH 16


/*
// 获取函数调用栈
int backtrace(void **buffer, int size);

 将调用栈中的函数地址转化为函数名称 并返回一个字符串数组
char **backtrace_symbols(void *const *buffer, int size);

//将调用栈中的函数地址转化为函数名称 并将其定入到文件中
void backtrace_symbols_fd(void *const *buffer, int size, int fd);
*/


void dumpTrace() {
    void *stack_trace[MAX_DUMP_STACK_DEPTH] = {0};
    char **stack_strings = NULL;
    int stack_depth = 0;
    int i = 0;

    //获取栈中各层调用函数地址
    stack_depth = backtrace(stack_trace, MAX_DUMP_STACK_DEPTH);

    //重找符号表，将函数调用地址转换为函数名称
    stack_strings = (char **)backtrace_symbols(stack_trace, stack_depth);
    for (i = 0; i < stack_depth; i++) {
        printf("[%d] %s \r\n", i, stack_strings[i]);
    }

    free(stack_strings);
    stack_strings = NULL;

    return ;
}

void test_methen() {
    dumpTrace();
}

void test_subMethond() {
    test_methen();
}

int main(int artc, char *argv[]) {
    test_subMethond();
    return 0;
}
