1. 常量定义
CC=g
2. 宏定义
-D

//gcc  --define-macro HELLO -DDEBUG ./gcc_macro.c && ./a.out
1. -D macro=string，等价于在头文件中定义：#define   macro   string。例如：-D TRUE=true，等价于：#define   TRUE   true
2. -D macro，等价于在头文件中定义：#define   macro   1，实际上也达到了定义：#define   macro的目的。例如：-D LINUX，等价于：#define   LINUX   1（与#define   LINUX作用类似）。
3. --define-macro   macro=string与-D macro=string作用相同。
