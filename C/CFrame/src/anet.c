
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

#include "../include/anet.h"

int anetSetError(char *err, const char *fmt, ...) {
    if (!fmt) {
        return ANET_ERR;
    }

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(err, ANET_ERR_LEN, fmt, ap);
    va_end(ap);

    return ANET_OK;
}

/**
 * 设置地址重用setsockopt SO_REUSEADDR
 * @param  err 错误描述
 * @param  fd  文件描述符
 *
 *
 * @return     int
 */
static int anetSetReuseAddr(char *err, int fd) {
    int yes = 1;
    printf("%d %d %lu\n", fd, yes, sizeof(yes));
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        anetSetError(err, "setsockopt SO_REUSEADDR failed :%s", strerror(errno));
        return ANET_ERR;
    }

    return ANET_OK;
}

static int anetCreateSocket(char *err, int domain) {
    int sock = socket(domain, SOCK_STREAM, 0);
    if (sock < 0) {
        anetSetError(err, "Create socket failed :%s", strerror(errno));
        return ANET_ERR;
    }

    //设置重用选项，可以多次close/open同一个socket
    if (ANET_ERR == anetSetReuseAddr(err, sock)) {
        close(sock);
        return ANET_ERR;
    }
    return sock;
}

static int anetListen(char *err, int s, struct sockaddr *addr, socklen_t len, int backlog) {
    if (bind(s, addr, len) == -1) {
        close(s);
        anetSetError(err, "bind failed:%s", strerror(errno));
        return ANET_ERR;
    }

    if (listen(s, backlog)) {
        close(s);
        anetSetError(err, "listen failed", strerror(errno));
        return ANET_ERR;
    }
    return ANET_OK;
}

static int _anetTcpServer(char *err, int port, char *bindaddr, int af, int backlog) {
    char _port[6];
    int rv, sock;
    struct addrinfo hints, *serverinfo, *p;

    snprintf(_port, 6, "%d", port);
    memset(&hints, '\0', sizeof(hints));
    hints.ai_family = af;       //协议族
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = AI_PASSIVE; //是否将取得的socket地址用于被动打开。

    if ((rv = getaddrinfo(bindaddr, _port, &hints, &serverinfo)) != 0) {
        anetSetError(err, "getaddrinfo failed %s", gai_strerror(rv));
        return ANET_ERR;
    }

    for (p = serverinfo; p != NULL; p = p->ai_next) {
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }

        //TODO IPV6 判断

        if (anetSetReuseAddr(err, sock) == ANET_ERR) {
            return ANET_ERR;
        }

        if (anetListen(err, sock, p->ai_addr, p->ai_addrlen, backlog) == ANET_ERR ) {
            return ANET_ERR;
        }
        break;
    }
    if (p == NULL) {
        anetSetError(err, "Unable to bind socket");
        return ANET_ERR;
    }

    if (serverinfo) {
        freeaddrinfo(serverinfo);
    }
    return sock;
}

static int anetGenericAccept(char *err, int sock, struct sockaddr *sa, socklen_t *len) {
    int fd;
    while (1) {
        if ((fd = accept(sock, sa, len) == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                anetSetError(err, "accept error :%s", strerror(errno));
                return ANET_ERR;
            }
        }
        break;
    }
    return fd;
}

int anetTcpServer(char *err, int port, char *bindaddr, int backlog) {
    return _anetTcpServer(err, port, bindaddr, AF_INET, backlog);
}

int anetTcp6Server(char *err, int port, char *bindaddr, int backlog) {
    return _anetTcpServer(err, port, bindaddr, AF_INET6, backlog);
}

int anetTcpAccept(char *err, int serversock, char *ip, size_t ip_len, int *port) {
    int fd;

    struct sockaddr sa;
    socker_t len;
    if ((fd = anetGenericAccept(err, serversock, &sa, &len)) == ANET_ERR) {
        close(s);
        return ANET_ERR;
    }

    if (sa.sin_family == AF_INET) { //ipv4

        if (ip) {

        }
        if (port) {
            
        }
    } else {//ipv6

    }
    return ANET_OK;
}
