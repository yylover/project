> socket编程
>

## 前置问题

1. unix socket 与TCP区别
2. IPV4 IPV6实现区别。
3. 网络字节序和主机字节序
4. bind 0.0.0.0 与127.0.0.1区别
5. TCP 三次握手与四次断开区别

http://c.biancheng.net/cpp/html/371.html
相关函数库:http://net.pku.edu.cn/~yhf/linux_c/

### 主要参考
http://blog.csdn.net/hguisu/article/details/7445768/
http://blog.csdn.net/cywosp/article/details/38965239
http://www.cnblogs.com/wmx-learn/p/5312259.html
http://www.cnblogs.com/skynet/archive/2010/12/12/1903949.html

## 文件描述符
### fd
系统为每一个进程维护了一个文件描述符表,该表的值从开始。所以在不同的进程中你会看到相同的文件描述符，
> 不同的进程中会出现相同的文件描述符，它们可能指向同一个文件，也可能指向不同的文件
>两个不同的文件描述符，若指向同一个打开文件句柄，将共享同一文件偏移量。因此，如果通过其中一个文件描述符来修改文件偏移量
> 与inode节点关系 http://blog.csdn.net/cywosp/article/details/38965239

### socket哲学
socket起源于Unix，而Unix/Linux基本哲学之一就是“一切皆文件”，都可以用“打开open –> 读写write/read –> 关闭close”模式来操作。

### 字节序
1. 大端字节序：整数的高位字节存储在内存的低地址处。小端字节序是指高位字节在内存的高地址处。
2. 现代计算机多是小端字节序，因此小端又称为主机字节序。

```
void byteorder() {
	union Data{
		short value;
		char union_bytes[sizeof(short)];
	} data;

	data.value = 0x0102;

	if (data.union_bytes[0] == 1 && data.union_bytes[1] == 2) {
		printf("big endian\n");
	} else if (data.union_bytes[0] == 2 && data.union_bytes[1] == 1) {
		printf ("little endian\n");
	} else {
		printf("unknown\n");
	}
}
```
#### 字节序转换主要函数

```
#include <netinet/in.h>
unsigned long int htonl(unsigned long int hostlong);
unsigned short int htons(unsigned short int hostshort);
unsigned long int ntohl(unsigned long int netlong);
unsigned short int ntohs(unsigned short int netshort);
```

#### IP地址转换函数
```
in_addr_t inet_addr(const char* strptr); //将点分十进制字符串转换为网络字节序整数表示的IPv4地址。失败返回IN_ADDR_NODE
int inet_aton(const char * cp, struct in_addr *inp);//同上，但是地址存在inp中，失败返回 0，成功1，
char * inet_ntoa(struct in_addr in); //将网络二进制的数字转换成网络地址,成功返回1，失败返回 0
//注意:::::inet_ntoa 不可重入，因为函数内部使用一个静态变量存储结果。

//下面是更新的函数，也能完成相同的功能。
int inet_pton(int af, const char *src, void *dst);
```

##  主要设计函数介绍
### socket函数:
用于创建一个文件描述符
```
int  socket(int protofamily, int type, int protocol);//返回sockfd
protofamily：即协议域，又称为协议族（family）。常用的协议族有，AF_INET(IPV4)、AF_INET6(IPV6)、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等等。协议族决定了socket的地址类型，在通信中必须采用对应的地址，如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合、AF_UNIX决定了要用一个绝对路径名作为地址。
type：指定socket类型。常用的socket类型有，SOCK_STREAM(TCP)、SOCK_DGRAM(UDP)、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等（socket的类型有哪些？）。
protocol：通常这个参数唯一，一般设置0。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议）。
```

### bind()函数(命名socket)

1. sockfd：即socket描述字，它是通过socket()函数创建了，唯一标识一个socket。bind()函数就是将给这个描述字绑定一个名字。
2. addr：一个const struct sockaddr*指针，指向要绑定给sockfd的协议地址。这个地址结构根据地址创建socket时的地址协议族的不同而不同：
3. 服务器通常要命名socket,而客户端通常不需要，os会自动分配socket地址。
4. 常见bind错误:
    * EACCESS:受保护的地址,仅超级管理员可以使用
    * EADDRINUSE:绑定的地址正在使用

```
int bind( int sockfd , const struct sockaddr * my_addr, socklen_t addrlen);
/**
 * socket 网络编程中，有通用的地址结构sockaddr,还有sockaddr_storage,不好用，涉及繁琐的位操作。因此Linux为各个协议族提供专门的socket地址结构，但所有的地址结构实际使用时要使用sockaddr。
 */
//如ipv4对应的是：
struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
};

/* Internet address. */
struct in_addr {
    uint32_t       s_addr;     /* IPv4,网络字节序 */
};
//ipv6对应的是：
struct sockaddr_in6 {
    sa_family_t     sin6_family;   /* AF_INET6 */
    in_port_t       sin6_port;     /* port number，网络字节序 */
    uint32_t        sin6_flowinfo; /* IPv6 flow information，流信息，设置为0 */
    struct in6_addr sin6_addr;     /* IPv6 地址结构体 */
    uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */
};

struct in6_addr {
    unsigned char   s6_addr[16];   /* IPv6 address */
};

//Unix域对应的是：
#define UNIX_PATH_MAX    108

struct sockaddr_un {
    sa_family_t sun_family;               /* 地质族:AF_UNIX */
    char        sun_path[UNIX_PATH_MAX];  /* 文件路径名 */
};
addrlen：对应的是地址的长度。
```


### listen connect

```
int listen(int sockfd, int backlog);
//backlog: 可排队的最大连接个数（监听队列的最大长度）。超过backlog,server不受理新的客户连接，客户端收到ECONNREFUSED错误信息。内核2.2之后，仅表示连接状态的socket上限，半连接状态的socket上限是:/proc/sys/net/ipv4/tcp_max_sync_backlog内核参数。

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//addr：地址
//addrlen: socket地址长度

```
1. listen系统调用创建一个监听队列用以存放待处理的客户连接。
2. server端调用socket(), bind(), listen()之后，就监听这个socket,client调用connnect()发起连接请求，server会受到并调用accept()接受这个请求.
3. listen 调用之后，Server就可以接受连接
4. backlog 指定最大连接数
```
//从listen 开始创建监听队列，就可以接收连接，backlog指定连接最大数，超过此数，其他的连接请求不再接受，如下:
localhost:50581->localhost:search-agent (ESTABLISHED)
localhost:50735->localhost:search-agent (ESTABLISHED)
localhost:50738->localhost:search-agent (ESTABLISHED)
localhost:50739->localhost:search-agent (SYN_SENT)
localhost:50740->localhost:search-agent (SYN_SENT)
localhost:50740->localhost:search-agent (SYN_SENT)
```
#### connect 常见错误
1. ECONNNREFUSED 目标端口不存在，连接被拒绝
2. ETIMEOUT: 连接超时

### accept
1. 从监听队列中接受一个连接。
2. 如果已经处于ESTABLISHED状态的连接，在accept直接断开了，那么accept仍然能成功。(因为accept只是从队列中取出连接，而无论连接状态。)
3.

```
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); //返回连接connect_fd
>sockfd:监听套接字
>addr:返回指定客户端地址。不感兴趣置成NULL
>len: 是输入参数,指向存有addr地址长度的整型数,
```
> accept会阻塞进程，直到连接建立并返回连接套接字。
>1. 监听套接字
>2. 连接套接字
>3. 一个server通常仅仅只需要创建一个监听socket,在服务器的生命周期会一直存在。

### close shutdown
1. close 不是立即关闭一个连接，而是将fd的引用计数减1.当fd引用计数为0时，真正关闭连接。shutdown 是立刻终止连接。

```
int close(int fd);
int shutdown(int sockfd, int howto);
//SHUT_RD: 关闭socket上读的一半
//SHUT_WR: 关闭socket上写的一半
//SHUT_RDWR: 关闭读写的一半
```

### read write()
1. read write文件读写函数适用于socket.但socket接口提供了专门的用于读写的调用，增加一些控制。
2. recv send 适用于tcp流数据读写,recv 返回读取到数据的长度，可能小于期望长度len，因此需要调用多次，c
3.
```
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);//
ssize_t write(int fd, const void *buf, size_t count);

#include <sys/types.h>
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags);//flags 通常为0
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
//Flags:
//MSG_CONFFIRM:(Send):链路层协议持续监听对方回应
//MSG_DONTROUTE:(send):不路由，直接发到本地局域网
//MSG_DONTWAIT:(BOTH):非阻塞
//MSG_MORE:(SEND):内核将超时等待新数据写入TCP发送缓冲区一并发送
//MSG_WAITALL:(receive):将读取到指定数量的字节才返回
//MSG_PEEK::窥探读取缓存数据，不会清楚。
//MSG_OOB::(BOTH):发送或接收紧急数据
//MSG_NOSIGNAL:往发送关闭管道写数据不引起SIGPIPE信号
返回值:阻塞模式发生错误EINTR, 非阻塞模式发生EAGAIN, EWOULDBLOCK是正常的。

//UDP数据读写
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
              const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                struct sockaddr *src_addr, socklen_t *addrlen);


//通用数据读写函数
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
```

1. read返回实际读取的字节数，0则已经读到文件结束。<0出现错误.
2. write,将buf中count字节写入文件描述符fd,失败返回-1，并设置errno变量。(网络程序中，0表示写了部分或全部数据，<0出现错误，根据具体的错误类型，EINTR表示出现中断错误，EPIPI表示网络连接有问题。对方关闭连接)

### 带外数据
内核通知应用程序带外数据的方式:
1. IO复用产生的异常事件和SIGURG信号
2. sockatmark(int sockfd);判断是否处于带外标记

### 地址信息函数
返回本地协议地址和远程协议地址
```
int getsockname(int sockfd, struct sockaddr * localaddr, socken_t * addrlen);
int getpeername(int sockfd, struct sockaddr * peeraddr, socken_t * addrlen);
```
### socket选项
fcntl是通用的控制文件描述符属性的方法。下面是专门读取设置socket文件描述符属性的方法。
1. 用的socket选项必须在listen之前调用，
2. SO_REUSERADDR 强制使用TIME_WAIT状态的socket连接，可以通过修改内核参数/proc/sys/net/ipv4/tcp_tw_recycle来修改，从而使得不进入TIME_WAIT状态，立刻释放连接。
3. SO_RECVBUF SO_SENDBUF 接收缓冲区和发送缓冲区
4. SO_RCVLOWAT SO_SNDLOWAT 接收和发送低水位选项
```
int setsockopt(int s, int level, int optname, const void * optval, ,socklen_toptlen);
int getsockopt(int s, int level, int optname, void* optval, socklen_t* optlen);
```

### 网络信息API
```
//完成主机名到地址解析，只支持IPV4, 且不允许调用者指定所需地址类型的任何信息
struct hostent *gethostbyname(const char *name);
//完成地址到主机名的解析
gethostbyaddr

getservbyname
getservbyport

//gethostbyname 和gethostbyaddr 已经由以下两个函数代替
getaddrinfo
getNameInfo

```

## 三次握手和四次断开
### SOCKET 三次握手

###
