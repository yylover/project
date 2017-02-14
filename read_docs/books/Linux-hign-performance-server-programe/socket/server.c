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

#define MAXLINE 4096

void log_fatal(char *str) {
	printf("%s\n", str);
	exit(0);
}

void log_info(char *str) {
	printf("%s\n", str);
	exit(0);
}

//当前主机字节序判断
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

/**
 *
 * unsigned long int inet_addr(const char *cp);//将网络地址转成二进制的数字
 */

int main() {

	char buf[4096];
	//int socket(int domain, int type, int protocol);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		log_fatal("socket failed");
	}

	//int bind(int sockfd, struct sockaddr * my_addr, int addrlen);
	struct sockaddr_in *socketaddr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    bzero(socketaddr, sizeof(struct sockaddr_in));
	socketaddr->sin_family = AF_INET;
	socketaddr->sin_port = htons(8000);
	socketaddr->sin_addr.s_addr = inet_addr("0.0.0.0");

	printf("size :%lu\n", sizeof(*socketaddr)); 	    //16
	printf("size :%lu\n", sizeof(struct sockaddr_in)); //16

	int res;
	res = bind(sockfd, (struct sockaddr *)socketaddr, sizeof(*socketaddr));
	if (res < 0) {
		log_fatal("bind failed");
	}
	printf("bind res :%d\n", res); //16

	//int listen(int s, int backlog);
	//backlog 能处理的最大连接数,如果到达最大连接数，client收到ECONNREFUSED错误,
	//Listen()并未开始接收连接, 只是设置socket 为listen 模式, 真正接收client 端连线的是accept().

	res = listen(sockfd, 10);
	if (res < 0) {
		log_fatal("listen failed");
	}

	int sock = accept(sockfd, NULL, NULL);
	if (res < 0) {
		log_fatal("accept failed");
	}


	for (int i = 0; i < 10; i ++) {
		struct msghdr msg;
		//int recvmsg(int s, struct msghdr *msg, unsigned int flags);
		int recres = recv(sock, buf, MAXLINE, 0);
		printf ("receive : %s\n", buf);

		char *str = "ok";
		send(sock, str, sizeof(str), 0);
	}
	//int accept(int s, struct sockaddr * addr, int * addrlen);
	//
	// res = accept(sockfd, NULL, NULL);





	close(sockfd);
	printf("Hello welcome here\n");
	return 1;
}
