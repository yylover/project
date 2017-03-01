

> C是一种通用的、面向过程式计算机程序设计语言。

## 数据类型
### 基本数据类型
 1. 整数 char unsigned char , signed char, int , unsigned int ,short, unsigned short, long ,unsigned long,
 2. 浮点数
 float:4
 double:8
 long double:10
 3. 枚举类型

 4. void类型
    1) 函数返回为空。
    2）函数参数为空:
    3） 指针指向void void*指针带别对象的指针，不是类型
5. 派生类型：
 1) 指针
 2) 数组
 3) 结构
 4) 共用体
 5) 函数

### 变量
1. 可操作存储区名称，类型决定存储的大小和布局。
2. 变量声明
```
extern int a;
定义： int a ;
初始化： a =10;
```
3. 函数声明、定义：
```
int fun()
int fun() {
 return 0;
}
```
4. 左值、右值
> 左值：指向内存位置的表达式称为左值。可以出现在赋值号左边或右边
> 右值：存储在内存中某些地址的数值，只能出现在右边。

### 常量

字面值：整数常量、浮点常量、字符常量、字符串常量。
定义常量：
 1) define #define LENGTH 10
 2) const: const int LENGTH 10;

### 存储类
定义程序中变量/函数的范围和生命周期。
1) auto:所有局部变量默认存储类。只能用在函数内。
2) register：存储在寄存器中，而不是RAM中的局部变量。
所以其最大尺寸大小是寄存器的大小，而且不能对其使用&操作符，因为没有内存位置。
3) static:指示编译器在程序生命周期内保持局部变量的存在。使用static修饰局部变量，可以在函数调用之间保持局部变量的值。
4) extern:提供一个全局变量引用，全局变量对所有的程序文件都可见。使用extern时，多个文件时，要使用其他文件定义的变量或函数，可以使用extern.

### 运算符

* 算数：+-*/ % ++ —
* 关系: == != > < >= <=
* 逻辑： && || !
* 位操作：  & | ^ ~ << >>
* 赋值： = += -= *= /= 
* 杂项：sizeof() 返回变量大小 & 变量地址
* 指向一个变量 ?: 条件表达式
* 优先级：

### 判断\循环

if else switch 
while do do while

### 函数
return_type function_name( parameter list );
1) 传值调用：
2) 引用传递

### 作用域
1) 函数/块内部局部变量
2) 函数外部的全局变量
3) 形式参数

局部变量被定义时，系统不会对其进行初始化，定义全局变量时，系统会自动进行初始化。
### 数组
1) 所有数组由连续内存外置组成，最低位置对应第一个元素。

2) 声明数组
type arrayName [ arraySize ];
3） 初始化数组：
 * double balance[4] = {0,4, 3, 4};
 * dance[2] =4;
4) 访问数组元素通过索引
1. 数组参数：
int *a, int a[], int a[10]


### 指针
1） 指针是一个变量，其值是另一个变量的地址，即内存位置的直接地址。
type *var_name;
2) 通过* 获取操作数指定变量地址的值。
3）null指针：
变量声明时，如果没有确切地址可以赋值，为指针赋值一个null值是一个好的编程习惯。
1. 指针算数运算
指针算数运算功能：向前或向后移动一个单元地址，因为数组名不能进行算数运算，所以常用指针遍历数组。
 指针比较：> < ==, 如果指针指向两个相关的变量，则可以进行比较。
2. 指针数组
 int *ptr[MAX]
3. 指针的指针

int **var;
4. 指针传递
5. 函数返回指针；
int * myFunc() {}
 C不支持在函数外返回局部变量的地址，除非定义局部变量为static变量。


### 字符串
1. c语言中，实际用null ‘\0'终止以为字符组成。因此一个null结尾的字符串，包含了组成字符串的字符。
2. 常见的字符串函数
```
strcpy(s1, s2)
strcat(s1, s2)
strlen(s2)
strcmp(s1, s2)
strchr(s1, ch)
strstr(s1, s2)
```
### 结构体
#### 定义结构
```
struct [structure tag]
{
   member definition;
   member definition;
   ...
   member definition;
} [one or more structure variables];
```
* 访问结构成员 .
*  指向结构的指针
struct structName *ptr;
ptr->elementId;

#### 位域
 有些信息存储时不需要占用完整的字节，只需要占几个或一个二进制位。C提供一种数据结构，称为位域或位段。
 ```
 struct 位域结构名
        { 位域列表 };
 类型说明符 位域名: 位域长度
struct bs{
    int a:8;
    int b:2;
    int c:6;
}data；
```
一个位域必须存储在同一个字节中，不能跨两个字节。
5. 

### 共同体union
允许在相同内存位置存储不同的数据类型。
union (union tag) {
 member de

### typedef
为类型设置别名。 typedef unsigned char byte ;
```
 typedef struct Books
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
} Book;
typedef #define 
```
  1) typedef仅限于为类型定义符号名称，#define不仅可以定义别名，还可以定义常量
 2) typedef 编译器执行，#define 预编译器执行。

### 输入、输出
stdin
stdout
stderr
```
getchar() putchar() 
char *gets(char*) 读取一行到s所指缓冲区，直到遇到一个终止符或EOF.
int puts(char *) 把字符串和一个尾随的换行符写入stdout
scanf()标准输入，
printf() 标准输出。
```
### 文件读写
```
FILE *fopen( const char * filename, const char * mode );
int fclose( FILE *fp );
int fputc( int c, FILE *fp );//错误返回EOF
int fputs( const char *s, FILE *fp );//成功返回非负值，错误返回EOF
int fgetc( FILE * fp );
char *fgets( char *buf, int n, FILE *fp );
size_t fread(void *ptr, size_t size_of_elements, 
             size_t number_of_elements, FILE *a_file);
              
size_t fwrite(const void *ptr, size_t size_of_elements, 
             size_t number_of_elements, FILE *a_file);
```
### 预处理器
C预处理器不过是文本替换的工具。指示编译器实际编译之前所需要完成的预处理。
```
#define
#include
#undef
#ifdef
#ifndef
#if
#else
#elif
#endif
#error: 当遇到标准错误输出时，输出错误消息
#pragma 向编译器发布特殊命令到编译器中。
```

2. 预定义宏:
```__DATA__ __TIME__ __FILE__ __LINE__ __STDC__```

3 .预处理运算符
 1) \ 宏延续运算符。
#define  message_for(a, b)  \
    printf(#a " and " #b ": We love you!\n")
 2) # 字符串常量化， 当需要把一个宏的参数转换为字符串常量 时，则使用字符串常量化运算符（#）。在宏中使用的该运算符有一个特定的参数或参数列表。
 3) ## 标记粘贴运算符
 合并两个参数，两个独立的标记合并为一个标记。
4. 参数化宏
```
#define square(x) ((x) * (x))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
```
### 头文件
头文件是.h文件，包含C函数声明和宏定义，被多个源文件引用共享。
建议把所有的常量、宏、系统全局变量和函数原型写在头文件中。
#include <>系统
#include “” 用户

2. 只引用一次头文件
```
#ifndef HEADER_FILE
#define HEADER_FILE

#endif
```
3. 有条件引用
有时需要从多个不同头文件中选择一个引用到程序中。
#if SYSTEM_!
 #include  “system1.h”
#elif SYSTEM_2
 #include “system2.h”
#endif

3. 

### 强制转换
(type_name) expression

### 错误处理
C不提供错误处理的支持，但允许以返回值形式允许访问底层数据。发生错误时，大部分函数会返回1或NULL， 同时设置一个错误代码errno.
程序初始化时，把 errno 设置为 0，这是一种良好的编程习惯。0 值表示程序中没有错误。
perror() 函数显示您传给它的字符串，后跟一个冒号、一个空格和当前 errno 值的文本表示形式。
strerror() 函数，返回一个指针，指针指向当前 errno 值的文本表示形式。
程序退出状态：
EXIT_SUCCESS
EXIT_FAILURE
### C 可变参数

### 内存管理
```
1   void *calloc(int num, int size);
该函数分配一个带有 function allocates an array of num 个元素的数组，每个元素的大小为 size 字节。
2   void free(void *address); 
该函数释放 address 所指向的h内存块。
3   void *malloc(int num); 
该函数分配一个 num 字节的数组，并把它们进行初始化。
4   void *realloc(void *address, int newsize); 
该函数重新分配内存，把内存扩展到 newsize。

《assert.h》
#define assert(ignore) ((void)0)
<ctype.h>
用来测试和映射字符。
1   int isalnum(int c)
该函数检查所传的字符是否是字母和数字。
2   int isalpha(int c)
该函数检查所传的字符是否是字母。
3   int iscntrl(int c)
该函数检查所传的字符是否是控制字符。
4   int isdigit(int c)
该函数检查所传的字符是否是十进制数字。
5   int isgraph(int c)
该函数检查所传的字符是否有图形表示法。
6   int islower(int c)
该函数检查所传的字符是否是小写字母。
7   int isprint(int c)
该函数检查所传的字符是否是可打印的。
8   int ispunct(int c)
该函数检查所传的字符是否是标点符号字符。
9   int isspace(int c)
该函数检查所传的字符是否是空白字符。
10   int isupper(int c)
该函数检查所传的字符是否是大写字母。
11   int isxdigit(int c)
该函数检查所传的字符是否是十六进制数字。
标准库还包含了两个转换函数，它们接受并返回一个 "int"
序号   函数 & 描述
1   int tolower(int c)
该函数把大写字母转换为小写字母。
2   int toupper(int c)
该函数把小写字母转换为大写字母。

<errno.h> 定义了证书变量eeno,通过系统调用设置，在错误事件中，某些库函数表明了什么发生了错误。

<float.h> 定义一组与浮点值相关的常量。
<limits.h> 定义各种变量类型的属性。最大值最小值
<locale> 定义低于设置
<math> 各种数学函数和一个宏
<setjmp> 定义了宏setjmp() longjmp() 和变量雷晓玲amp_bug.
<signal> 定义了一个变量类型sig_atomic_t,两个函数调用和一些宏来处理程序执行期间报告的不同信号。
< stddef.h> 定义了各种变量类型和宏

<stdio.h> 头文件定义了三个变量，一些宏
<stdlib.h> 定义了四个变量类型一些工具函数
<string.h> 函数处理
<time> 事件处理
```
