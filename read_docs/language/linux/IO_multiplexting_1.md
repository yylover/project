> IO多路复用
>



>I/O多路复用就通过一种机制，可以监视多个描述符，一旦某个描述符就绪（一般是读就绪或者写就绪），能够通知程序进行相应的读写操作。但select，poll，epoll本质上都是同步I/O，因为他们都需要在读写事件就绪后自己负责进行读写，也就是说这个读写过程是阻塞的，而异步I/O则无需自己负责进行读写，异步I/O的实现会负责把数据从内核拷贝到用户空间。
>

---

>I/O复用使得程序能同时监听多个文件描述符，这对于提高程序性能至关重要。

主要的适用场景:
- 1. 同时处理多个socket
- 2. 需要同时处理用户输入和网络连接
- 3. TCP server需要同时处理监听socket和连接socket。（最多的适用场景）
- 4. server同时处理TCP请求和UDP请求。
- 5. 服务器同时处理多个端口或多种服务。

- **I/O复用虽然能同时监听多个文件描述符。但本身是阻塞的。当同时多个fd就绪时，只能串行处理。要实现并发，只能采用多进程或多线程手段。**

## select 系统调用

1. fd_set是long型数组，最大包括1024个大小。
2. 写就绪事件:
    1) socket内核发送缓存区可用字节数大于或等于SO_SNDLOWAT,
    2) socket写操作被关闭。(对此socket写出发SIGPIPE)
    3) socket使用非阻塞connect连接成功或失败(超时)
    ) socket有未处理的错误。(使用getsockopt读取和清除错误)
3. 读就绪事件:
    1) socket接收缓存区中字节数大于等于低水平标记SO_RCVLOWAT
    2) socket通信对方关闭连接。（读操作返回0）
    3) 监听socket上有新的连接请求
    4) socket上有未处理的错误。


```
#include <sys/select.h>

fd_set set;
FD_ZERO(&set); /*将set清零使集合中不含任何fd*/
FD_SET(fd, &set); /*将fd加入set集合*/
FD_CLR(fd, &set); /*将fd从set集合中清除*/
FD_ISSET(fd, &set); /*来检测fd是否在set集合中*/
/**
 * select函数说明
 * @param  nfds      被监听的文件描述符总数，通常设置为最大描述符+1
 * @param  readfds   可读事件对应的文件描述符集合
 * @param  writefds  可写事件对应的文件描述符集合
 * @param  exceptfds 异常事件对应的文件描述符集合
 * @param  timeout   最多等待时间,NULL时阻塞读。同时提供了一种毫秒定时的方式。都是0，非阻塞读，立刻返回。
 * @return           成功返回就绪的可读、可写、异常文件描述符总数，0，定时结束没有事件，-1 失败
 */
int select( int nfds, fd_set FAR* readfds,　fd_set * writefds, fd_set * exceptfds,　const struct timeval * timeout);

```

```
//select 读取OOB异常事件
    fd_set read_sets, except_sets;
    FD_ZERO(&read_sets);
    FD_ZERO(&except_sets);

    char buf_read[100];
    int ret;
    while (1) {
        memset(buf_read, 0, sizeof buf_read);
        //每次select之前要重新设置read_sets, except_sets状态，因为select时被内核修改。
        FD_SET(sock, &read_sets);
        FD_SET(sock, &except_sets);

        res = select(sock+1, &read_sets, NULL, &except_sets, NULL);
        if (res < 0) {
            log_fatal("select error");
        }

        //普通事件，用普通的recv读取
        if (FD_ISSET(sock, &read_sets)) { //正常数据
            ret = recv(sock, buf_read, sizeof(buf_read), 0);
            if (ret == 0) { //已经断开连接
                break;
            }
            printf("got %d bytes of normal data:%s\n", ret, buf_read);
        }

        memset(buf_read, 0, sizeof buf_read);
        if (FD_ISSET(sock, &except_sets)) { //带外数据
            //OOB事件，用MSG_OOB读取
            ret = recv(sock, buf_read, sizeof(buf_read), MSG_OOB);
            if (ret <= 0) {
                printf("%s\n", "没有异常数据");
                break;
            }
            printf("got %d bytes of oob data:%s\n", ret, buf_read);
        } else {
            log_fatal("error");
        }
    }
```
### poll

1. poll 系统调用跟select类，也是指定事件内轮询一定数量的文件描述符，只是描述fd集合方式不同。
2. poll没有fd个数的限制，只不过fd数量多时，效率会线性下降。
3.

```
struct pollfd {
    int fd;        //文件描述符
    short events;  //注册的事件
    short revents; //实际发生的事件，由内核填充
};

/**
 * poll函数原型
 * @param  fd      pollfd结构数组
 * @param  nfds    监听的集合大小，typedef unsigned long int nfds_t;
 * @param  timeout 超时值，单位是毫秒,-1 永远阻塞，0 非阻塞， >0
 * @return         成功返回就绪的描述符总数，0 超时， -1 失败
 */
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```
### epoll

1. epoll是poll和select的改进

```
/**
 * epoll_create
 * @param  size size现在并不起作用，只是给内核一个提示，告诉他时间表多大。
 * @return      fd
 */
int epoll_create(int size);

struct epoll_event {
    __uint32_t events; //epoll事件，与Poll基本相同，添加EPOLLET,EPOLLONESHOT
    epoll_data_t data; //用户数据
}

typedef union epoll_data {
    void *ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
};

/**
 * epoll_ctl 函数描述
 * @param  epfd  要操作的文件描述符
 * @param  op    操作类型,EPOLL_CTL_ADD,EPOLL_CTL_MOD,EPOLL_CTL_DEL
 * @param  fd    要操作的文件描述符
 * @param  event 指定事件
 * @return       成功0，失败-1
 */
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

/**
 * epoll_wait 函数声明
 * @param  epfd      fd
 * @param  events    由内核修改，如果有事件发生，就设置这个参数
 * @param  maxevents 指定最多监听多少个事件。必须>0
 * @param  timeout   与poll接口相同
 * @return           成功时返回就绪个数，失败返回-1
 */
int epoll_wait(int epfd, struct epoll_event *events, int maxevents,int timeout);

```
#### poll和epoll工作方式的对比:

```
/*如何索引poll返回的就绪文件描述符*/
int ret = poll(fds, MAX_EVENTS_NUMBER, -1);
//必须遍历所有已注册文件描述符并找到其中的就绪者
for (int i = 0; i < MAX_EVENTS_NUMBER; i++) {
    //判断第i个fd是否就绪
    if (fds[i].revents & POLLIN) {
        int sockfd = fds[i].fd;
    }
}

/*如何索引epoll返回的就绪文件描述符*/
int ret = epoll_wait(epollfd, events, MAX_EVENTS_NUMBER, -1);
for (int i = 0; i< ret; i++) {
    int sockfd = events[i].data.fd;
    /*sockfd 肯定就绪，直接处理 */
}
```

### LT ET
LT: level trigger,电平触发。epoll检测到其上有时间发生并通知应用程序后，可以不立即处理，当下次epoll_wait 调用时，仍然反馈该事件。
ET: edge trigger:边沿触发。在内核事件表中注册一个EPOLLET事件，在该模式下，应用程序必须立即处理，后续的epoll_wait不再通知这一事件。


## 三种方式区别

系统调用 | select | poll | epoll
---|---|---|---
事件集合 | | column3 | column4
索引就绪文件描述符的复杂度 | O(n) | O(n) | O(1)
最大支持fd数 |有最大值限制 | 65535 | 65535
工作模式 | LT | LT | 支持ET高效模式
内核实现 | 轮训 O(n)| 轮训O(n) | 回调方式检测，O(1)
