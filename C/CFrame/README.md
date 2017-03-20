Target:
    基本数据结构
        array vector list adlist stack queue dict string
    Linux socket:
    进程/线程
    IP复用 select poll epoll kqueue
    信号: 定时器、IP复用、文件
    锁:
### 其他:
    so: 动态链接库
    C 函数指针的含义
    静态函数只能被文件内部使用了，


问题:
msd_hash.c 内存泄露: clear时





1. C语言类型
    没有bool类型，只能用bool来代替。对int而言，非0都是true
2. 规范

3.

#### 指针函数 函数指针
1. 指针函数：当一个函数声明其返回值为一个指针时，实际上就是返回一个地址给调用函数，比如:int *GetDate();
2. 函数指针:指向函数的指针包含了函数的地址，可以通过它来调用函数。例如:类型说明符 (*函数名)(参数)

#### 函数
1. C空参数要明确声明
int empty(void)
2. 空指针: NULL,必须是大写



3. 内存分配区别
```
void *malloc( size_t size );
void *calloc( size_t numElements, size_t sizeOfElement );
void *realloc(void* ptr, unsigned newsize);
```
主要的不同是malloc不初始化分配的内存，已分配的内存中可以是任意的值.　calloc　初始化已分配的内存为0。次要的不同是calloc返回的是一个数组，而malloc返回的是一个对象。

### 单元测试框架cmockery
cmockery 是google 提供的轻量级C语言测试框架
https://github.com/google/cmockery

http://c4fun.cn/blog/2014/12/06/cmockery/

#### 断言

```
assert_true(c)
assert_false(c)
assert_int_equal(a, b)
assert_int_not_equal(a, b)
assert_string_equal(a, b)
assert_string_not_equal(a, b)
assert_memory_equal(a, b, size)
assert_memory_not_equal(a, b, size)
assert_in_range(value, minimum, maximum)
assert_not_in_range(value, minimum, maximum)
assert_in_set(value, values, number_of_values)
assert_not_in_set(value, values, number_of_values)

```

#### 使用

gcc calc_test.c calc.c -lcmockery
