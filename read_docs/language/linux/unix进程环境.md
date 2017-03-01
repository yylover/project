
## 进程环境
> main 如何调用,命令行参数如何传递?
> 存储器布局？如何分配额外存储空间
> 进程如何使用环境变量

### main

> int main(int argc, char *argv[]);
内核调用c程序时，先调用一个特殊的启动例程，可执行文件将此启动例程指定为程序的起始地址，启动例程从内核获取命令行参数和环境变量。

### 进程终止

### 退出

_exit 立即进入内核，exit()先执行一些清理（调用执行各终止处理程序，关闭所有标准IO流）

#### 终止处理程序
> int atexit(void (*func)(void));
> 调用顺序按照添加顺序逆序调用。
http://7ktumn.com1.z0.glb.clouddn.com/WechatIMG3.jpeg

1. 内核使程序执行的唯一方法是调用exec()

### 命令行参数

> ./a.out first second third
> argv[0]  [1]   [2]    [3]

### 环境变量
环境表也是一个字符指针数组，每个指针包含一个以null结束的字符串地址。
```
int main(int argc, char *argv[], char *envp[]) {
    for (int i=0; envp[i]!= NULL;i++) {
        printf("%s\n", envp[i]);
    }
}
```

### c 程序存储空间布局

1. 正文段:CPU执行机器指令的部分， 通常是可以共享的，而且是只读的。
2. 初始化数据段。包含程序中需要赋初始值的变量
3. 非初始化数据段bss, long sum[1000], 内核将此段初始化为0
4. 栈: 自动变量已经函数调用时需要保存的信息。
5. 堆： 通常在堆中进行动态分配。

http://7ktumn.com1.z0.glb.clouddn.com/WechatIMG6.jpeg

```
//size 可以查询正文段，数据段和bss段大小
# size /usr/bin/cpp
   text	   data	    bss	    dec	    hex	filename
 260678	   3704	   2952	 267334	  41446	/usr/bin/cpp
```

### 环境变量
```
char *getenv(const char *name);
int setenv(const char *name, const char *value, int rewrite);
void unsetenv(const char *name);
```

### 自动、寄存器和易失变量

### 资源限制
```
int getrlimit(int resource, struct rlimit *rpstr);
int setrlimit(int resource, const struct rlimit *rpstr);
```


## 进程控制
> 进程创建、执行和终止
> 进程id:实际、有效和组id

### 进程标识
1. 每个进程有唯一的进程ID,0 调度进程，常称为交换进程swapper. 1:init进程，负责在内核自举后启动一个unix系统 2：页精灵进程，负责支持虚存系统的请页操作。

### fork 创建进程
父子进程对fd是共享的。
### vfork
### exit
### wait waitpid
### 竟态条件
### 更改用户id和组id

## 进程关系

### 进程组
每个进程有一个进程id之外，还属于一个进程组。

### session 会话组
session 是一个或多个进程组集合。

### 控制终端:

### shell 执行程序：

### 孤儿进程组

## daemon进程

## IPC

## 高级IPC
