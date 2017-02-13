/*****************************************************************************
Copyright: 2017~2030 yangqiang personal
File name: anet.h
Description: Basic Tcp socket stuff made a bit less boring .Derived from redis
Author: yangqiang
Version: 1.0
Date:
History:

getsockopt: 1. len 是输入项，不是输出项。2. SO_REUSEADDR 如果值为true,取出来是4


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
int anetUnitxConnect(char *err, char *path);
int anetUnitNonblockConnect(char *err, char *path);

int anetRead(int fd, char *buf, int count);
int anetWrite(int fd, char *buf, int count);
int anetResolve(char *err, char *host, char *buf, int count);
int anetResolveIP(char *err, char *host, char *buf, int count);

int anetTcpServer(char *err, int port, char *bindaddr, int backlog);
int anetTcp6Server(char *err, int port, char *bindaddr, int backlog);
// int anetUnitxServer(char *err, char *path, mode_t perm, int backlog);

int anetTcpAccept(char *err, int serversock, char *ip, size_t ip_len, int *port);
int anetUnixAccept(char *err, int serversock);

int anetBlcok(char *err, int fd);
int anetNonBlock(char *err, int fd);
int anetEnableTcpNoDelay(char *err, int fd);
int anetDisableTcpNoDelay(char *err, int fd);
int anetTcpKeepAlive(char *err, int fd);
int anetKeepAlive(char *err, int fd, int interval);
int anetSendTimeout(char *err, int fd, long long ms);

int anetPeerToString(int fd, char *ip, size_t ip_len, int *port);
int anetSockname(int fd, char *ip, size_t ip_len, int *port);


#endif
