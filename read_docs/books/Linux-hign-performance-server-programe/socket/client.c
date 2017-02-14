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


void data_send_test(int connfd) {
	char *oob_data = "abc";
	char *nor_data = "123";

	send(connfd, nor_data, strlen(nor_data), 0);
	send(connfd, oob_data, strlen(oob_data), MSG_OOB);
	send(connfd, nor_data, strlen(nor_data), 0);
}
/**
 *
 *
 *
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

	printf("%d\n", sockfd);

	//int bind(int sockfd, struct sockaddr * my_addr, int addrlen);
	struct sockaddr_in *socketaddr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
    bzero(socketaddr, sizeof(struct sockaddr_in));
	socketaddr->sin_family = AF_INET;
	socketaddr->sin_port = htons(8000);
	socketaddr->sin_addr.s_addr = inet_addr("0.0.0.0");

	printf("size :%lu\n", sizeof(*socketaddr)); 	    //16
	printf("size :%lu\n", sizeof(struct sockaddr_in)); //16

	int res;
	res = connect(sockfd, (struct sockaddr *)socketaddr, sizeof(*socketaddr));
	if (res < 0) {
		log_fatal("connect failed");
	}
	printf("connect res :%d\n", res); //16

	data_send_test(sockfd);
	return 0;

	for (int i = 0; i < 10; i ++) {
		struct msghdr msg;
		//int recvmsg(int s, struct msghdr *msg, unsigned int flags);
		// int recres = recvmsg(sock, &msg, 0);
		// sendmsg();
		char *str = "Hello";
		send(sockfd, str, sizeof(str), 0);

		int recres = recv(sockfd, buf, MAXLINE, 0);
		printf ("receive : %s\n", buf);
	}


	close(sockfd);
	printf("Hello welcome here\n");
	return 1;
}
