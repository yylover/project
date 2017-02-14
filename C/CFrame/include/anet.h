/*****************************************************************************
Copyright: 2017~2030 yangqiang personal
File name: anet.h
Description: Basic Tcp socket stuff made a bit less boring .Derived from redis
Author: yangqiang
Version: 1.0
Date:
History:

getsockopt: 1. len 是输入项，不是输出项。2. SO_REUSEADDR 如果值为true,取出来是4
socket: 默认是阻塞的，
socket: 设置非阻塞再设置阻塞后得到的ip错误。

3. Nagle算法:
Nagle算法的基本定义是任意时刻，最多只能有一个未被确认的小段。 所谓“小段”，指的是小于MSS尺寸的数据块，所谓“未被确认”，是指一个数据块发送出去后，没有收到对方发送的ACK确认该数据已收到。

      Nagle算法的规则（可参考tcp_output.c文件里tcp_nagle_check函数注释）：

    （1）如果包长度达到MSS，则允许发送；

    （2）如果该包含有FIN，则允许发送；

    （3）设置了TCP_NODELAY选项，则允许发送；

    （4）未设置TCP_CORK选项时，若所有发出去的小数据包（包长度小于MSS）均被确认，则允许发送；
    （5）上述条件都未满足，但发生了超时（一般为200ms），则立即发送。

4. Unix Server connect 暂时没有写
5.

*****************************************************************************/


#ifndef __ANET_H_
#define __ANET_H_

#define ANET_OK 0
#define ANET_ERR -1
#define ANET_ERR_LEN 256

int anetSetError(char *err, const char *fmt, ...);//加到头文件是为了测试

int anetTcpConnect(char *err, char *addr, int port);
int anetTcpNonblockConnect(char *err, char *addr, int port);
int anetTcpNonblockBindConnect(char *err, char *addr, int port, char *souceaddr);
int anetTcpNonBlockBestEffortBindConnect(char *err, char *addr, int port, char *source_addr);
int anetUnixConnect(char *err, char *path);
int anetUnixNonblockConnect(char *err, char *path);

int anetRead(int fd, char *buf, int count);
int anetWrite(int fd, char *buf, int count);
int anetResolve(char *err, char *host, char *buf, int count);
int anetResolveIP(char *err, char *host, char *buf, int count);

int anetTcpServer(char *err, int port, char *bindaddr, int backlog);
int anetTcp6Server(char *err, int port, char *bindaddr, int backlog);
// int anetUnitxServer(char *err, char *path, mode_t perm, int backlog);

int anetTcpAccept(char *err, int serversock, char *ip, size_t ip_len, int *port);
int anetUnixAccept(char *err, int serversock);

int anetBlock(char *err, int fd);
int anetNonBlock(char *err, int fd);
int anetEnableTcpNoDelay(char *err, int fd);
int anetDisableTcpNoDelay(char *err, int fd);
int anetTcpKeepAlive(char *err, int fd);
int anetKeepAlive(char *err, int fd, int interval);
int anetSendTimeout(char *err, int fd, long long ms);

int anetPeerToString(int fd, char *ip, size_t ip_len, int *port);
int anetSockname(int fd, char *ip, size_t ip_len, int *port);


#endif
