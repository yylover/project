#include <sys/select.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h> // for close
#include <stdlib.h> //exit
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

struct pollfd {
    int fd;        //文件描述符
    short events;  //注册的事件
    short revents; //实际发生的事件，由内核填充
};

/**
 * poll函数原型
 * @param  fd      pollfd结构数组
 * @param  nfds    监听的集合大小，typedef unsigned long int nfds_t;
 * @param  timeout 超时值，单位是毫秒
 * @return         成功返回就绪的描述符总数，0 超时， -1 失败
 */
int poll(struct pollfd *fds, nfds_t nfds, int timeout);



/**
 * [select description]
 * @param  nfds      被监听的文件描述符总数，通常设置为最大描述符+1
 * @param  readfds   可读事件对应的文件描述符集合
 * @param  writefds  可写事件对应的文件描述符集合
 * @param  exceptfds 异常事件对应的文件描述符集合
 * @param  timeout   最多等待时间,NULL时阻塞读。同时提供了一种毫秒定时的方式。
 * @return           成功返回就绪的可读、可写、异常文件描述符总数，0，定时结束没有事件，-1 失败
 */
//int select( int nfds, fd_set FAR* readfds,　fd_set * writefds, fd_set * exceptfds,　const struct timeval * timeout);





void log_fatal(char *str) {
	printf("%s\n", str);
	exit(0);
}

int main() {

	char buf[4096];
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		log_fatal("socket failed");
	}

	//int bind(int sockfd, struct sockaddr * my_addr, int addrlen);
	struct sockaddr_in *socketaddr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    memset(socketaddr, '\0', sizeof(struct sockaddr_in));
	socketaddr->sin_family = AF_INET;
	socketaddr->sin_port = htons(8000);
	socketaddr->sin_addr.s_addr = inet_addr("0.0.0.0");

	int res;
	res = bind(sockfd, (struct sockaddr *)socketaddr, sizeof(*socketaddr));
	if (res < 0) {
		log_fatal("bind failed");
	}

	//int listen(int s, int backlog);
	//backlog 能处理的最大连接数,如果到达最大连接数，client收到ECONNREFUSED错误,
	//Listen()并未开始接收连接, 只是设置socket 为listen 模式, 真正接收client 端连线的是accept().
	res = listen(sockfd, 10);
	if (res < 0) {
		log_fatal("listen failed");
	}

    struct sockaddr_in client_addr;
    memset(&client_addr, '\0', sizeof client_addr);
    socklen_t client_len = sizeof client_addr;
	int sock = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
	if (res < 0) {
		log_fatal("accept failed");
	}

    char remoteAddr[20];
    printf("connected success with ip:%s and port:%d\n", inet_ntop(AF_INET, &client_addr.sin_addr, remoteAddr, 20), ntohs(client_addr.sin_port));

    //打印client 的地址
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

    close(sock);
	close(sockfd);
	printf("Hello welcome here\n");
	return 1;
}
