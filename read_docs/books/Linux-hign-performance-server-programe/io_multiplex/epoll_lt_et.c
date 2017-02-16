#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> // for close
#include <stdlib.h> //exit
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>

/**
 * LT: 同一个事件会多次提示，上一次没读取完成也可以继续操作.
 * ET: 同一个读写事件只会提示一次，务必保证一次读取完所有数据。
 *
 * epoll:EPOLLONESHOT 保证一个socket的事件同一时间只会触发一个，这样保证了只有一个线程在处理该socket
 *
 */

#define MAX_EVENTS_NUMBER 1024
#define BUFFER_SIZE 10

void log_fatal(char *str) {
	printf("%s\n", str);
	exit(0);
}

/**
 * 设置非阻塞模式
 * @param  fd 文件描述符
 * @return    原来的fd属性
 */
int setNonblock(int fd) {
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        log_fatal("fcntl F_GETFL failed");
    }
    int new_flags = flags | O_NONBLOCK;
    if (fcntl(fd, F_SETFL, new_flags) == -1) {
        log_fatal("fcntl F_SETFL failed");
    }
    return flags;
}

void addFd(int epollid, int fd, int enable_et) {
    struct epoll_event ee;
    ee.data.fd = fd;
    ee.events = EPOLLIN; //注册读事件
    if (enable_et) {
        ee.events |= EPOLLET;
    }

    if (epoll_ctl(epollid, EPOLL_CTL_ADD, fd, &ee) == -1) {
        log_fatal("epoll_ctl addfd failed");
    }
    setNonblock(fd); //将此文件描述符设置为非阻塞模式
}

void addfd_oneshot(int epollid, int fd, int enable_oneshot) {
    struct epoll_event ee;
    ee.data.fd = fd;
    ee.events = EPOLLIN|EPOLLET; //注册读事件
    if (enable_oneshot) {
        ee.events |= EPOLLONESHOT;
    }
    if (epoll_ctl(epollid, EPOLL_CTL_ADD, fd, &ee) == -1) {
        log_fatal("epoll_ctl addfd failed");
    }
    setNonblock(fd); //将此文件描述符设置为非阻塞模式
}

//重置EPOLLONESHOT事件，这样操作之后，即使fd上EPOLLONESHOT被注册，这样仍然会触发EPOLLIN事件
void reset_oneshot(int fd) {
    struct epoll_event ee;
    ee.data.fd = fd;
    ee.events = EPOLLIN|EPOLLET|EPOLLONESHOT; //注册读事件
    if (epoll_ctl(epollid, EPOLL_CTL_MOD, fd, &ee) == -1) {
        log_fatal("epoll_ctl addfd failed");
    }
}

/**
 * lt工作模式
 * @param ee       发生的时间数组
 * @param number   发生的事件个数
 * @param epollfd  epoll fd
 * @param listenfd 监听socket fd
 */
void lt(epoll_event * ee, int number, int epollfd, int listenfd) {
    int i = 0;
    char buf[BUFFER_SIZE];
    for (i = 0; i < number ;i ++) {
        if (listenfd == ee[i].data.fd) { //新的socket连接请求
            struct sockaddr_in client_addr;
            memset(&client_addr, '\0', sizeof client_addr);
            socklen_t client_len = sizeof client_addr;
            int sock = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
            if (res < 0) {
                log_fatal("accept failed");
            }

            addFd(epollfd, sock, 0);
        } else if (ee[i].events && EPOLLIN) { //可读事件
            //只要socket中还有未读出的数据，这段代码会被不断触发
            memset(buf, 0, BUFFER_SIZE);
            int ret = recv(ee[i].data.fd, buf, BUFFER_SIZE-1, 0);
            if (ret <= 0) {
                close(ee[i].data.fd);
                continue;
            }
            printf("Got %d bytes of data :%s\n", ret, buf);
        } else {
            printf("%s\n", "something else happened");
        }
    }
}

//et 对于一次socket读事件，要保证所有数据全部读出
void et(epoll_event *ee, int number , int epollfd, int listenfd) {
    char buf[BUFFER_SIZE];
    for (i = 0; i < number ;i ++) {
        int sockfd = ee[i].data.fd;
        if (listenfd == sockfd) { //新的socket连接请求
            struct sockaddr_in client_addr;
            memset(&client_addr, '\0', sizeof client_addr);
            socklen_t client_len = sizeof client_addr;
            int sock = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
            if (res < 0) {
                log_fatal("accept failed");
            }

            addFd(epollfd, sock, 1);
        } else if (ee[i].events && EPOLLIN) { //可读事件
            //这段代码不会被重复触发，因此我们需要循环读取数据，确保socket中数据全部读出
            memset(buf, 0, BUFFER_SIZE);
            while (1) {
                int ret = recv(sockfd buf, BUFFER_SIZE-1, 0);
                if (ret == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        //已经全部读取完成
                        printf("read later");
                        break;
                    }
                    close(sockfd);
                    break;
                } else if (ret == 0) {
                    //socket已经关闭
                    close(sockfd);
                } else {
                    printf("Got %d bytes of data :%s\n", ret, buf);
                }
            }

        } else {
            printf("%s\n", "something else happened");
        }
    }
}

struct fds {
    int epollid;
    int sockfd;
} fds;


void* worker(void *data) {
    fds *fds_data = (struct fds *)data;
    int sockfd = fds_data->sockfd;
    int epollid = fds_data->epollid;

    char buf[BUFFER_SIZE];
    memset(buf, 0, BUFFER_SIZE);
    while (1) {
        int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
        if (ret == 0) { //socket 关闭
            close(sockfd);
            break;
        } else if (ret == -1) {
            if (errno == EAGAIN) { //已经读取完成
                reset_oneshot(sockfd);
                break;
            }
        } else {
            printf("get content %s\n", buf);
        }
    }

    //读取数据完成
}

void et_oneshot(epoll_event *ee, int number, int epollid, int listenfd) {
    for (int i = 0; i < number ;i ++) {
        int sockfd = ee[i].data.fd;
        if (listenfd == sockfd) {
            struct sockaddr_in client_addr;
            memset(&client_addr, 0, sizeof client_addr);
            socklen_t *client_len = sizeof client_addr;
            int sock = accept(listenfd, &client_addr, &client_len);
            if (sock < 0) {
                log_fatal("accept failed");
            }

            addfd_oneshot(epollid, sock, 1);
        } else if (ee[i].events & EPOLLIN) {// socket可读
            //创建一个新的线程来处理该事件
            pthread_t pthread;
            fds fds_new_worker;
            fds_new_worker.epollid = epollid;
            fds_new_worker.sockfd = sockfd;
            pthread_create(&pthread, NULL, worker, (void *)&fds_new_worker);
        } else {
            printf("something else happened\n");
        }
    }
}


int main() {

	char buf[4096];
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

	struct sockaddr_in *socketaddr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    memset(socketaddr, '\0', sizeof(struct sockaddr_in));
	socketaddr->sin_family = AF_INET;
	socketaddr->sin_port = htons(8000);
	socketaddr->sin_addr.s_addr = inet_addr("0.0.0.0");

	int res;
	res = bind(sockfd, (struct sockaddr *)socketaddr, sizeof(*socketaddr));
    assert(res != -1);

	//int listen(int s, int backlog);
	//backlog 能处理的最大连接数,如果到达最大连接数，client收到ECONNREFUSED错误,
	//Listen()并未开始接收连接, 只是设置socket 为listen 模式, 真正接收client 端连线的是accept().
	res = listen(sockfd, 10);
    assert(res != -1);

    struct epoll_event events[MAX_EVENTS_NUMBER];
    int epollid = epoll_create(5);
    assert(epollid != -1);
    addFd(epollid, int sockfd, 0);
    // addFd(epollid, int sockfd, 1); et

    while (1) {
        int ret = epoll_wait(epollid, events, MAX_EVENTS_NUMBER, -1);
        if (ret < 0) {
            log_fatal("epoll_wait failed");
        }

        //lt 工作模式
        lt(events, ret, epollid, sockfd);
        //et 工作模式
        // et(events, ret, epollid, sockfd);
        // et 带有EPOLLONESHOT工作模式
        // et_oneshot(events, ret, epollid, sockfd);
    }

    close(sockfd);
    return 0;
}
