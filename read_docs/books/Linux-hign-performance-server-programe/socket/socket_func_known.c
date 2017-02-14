#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <libgen.h>
//字节序判断
/**
## socket 地址
### 通用socet 地址
```
struct sockaddr {
	sa_family_t    sa_family;  #AF_UNIX AF_INET AF_INET6
	char           sa_data[14];
};
```
### 14字节的sa_data 无法容纳AF_INET6 和AF_UNIX地址长度，因此linux定义了新的通用的socket地址结构:

```
#define _SS_ALIGNSIZE (sizeof (int64_t))
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof (sa_family_t))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof (sa_family_t)+
                              _SS_PAD1SIZE + _SS_ALIGNSIZE))
struct sockaddr_storage {
    sa_family_t  ss_family;      // address family
    char _ss_pad1[_SS_PAD1SIZE]; // Following fields are implementation specific
    int64_t _ss_align; 			 // 可以使内存对其
    char _ss_pad2[_SS_PAD2SIZE];
};
```
### 专用socket地址
上面的两个socket地址结构体不好用，因此linux为各个协议族定义了专用的socket结构体。
```
//unix 本地域协议族
struct sockaddr_un {
	sa_family_t sun_family;
	char        sun_path[];
};

//IPV4
 struct sockaddr_in {
    sa_family_t    sin_family;
    in_port_t      sin_port;
    struct in_addr sin_addr;
};

struct in_addr {
    uint32_t       s_addr;
};
//IPV6
struct sockaddr_in6 {
    sa_family_t     sin6_family;
    in_port_t       sin6_port;
    uint32_t        sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t        sin6_scope_id;
};

struct in6_addr {
    unsigned char   s6_addr[16];
};
```
*/

typedef int bool;
#define true 1
#define false 0

/*
 * ip地址转换函数，
unsigned long int inet_addr(const char *cp); //将点分十进制字符串转换为网络字节序整数表示的IPv4地址。失败返回IN_ADDR_NODE
int inet_aton(const char * cp, struct in_addr *inp);//同上，但是地址存在inp中，失败返回 0，成功1，
char * inet_ntoa(struct in_addr in); //将网络二进制的数字转换成网络地址,成功返回1，失败返回 0

//更新的函数
int inet_pton(int af, const char *src, void *dst);
const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);


163.13.132.68 inet_addr is 1149504931
163.13.132.68 inet_aton is 1149504931
1149504931 inet_ntoa is 163.13.132.68
163.13.132.68 inet_pton is 1149504931
1149504931 inet_ntop is 163.13.132.68
*/
void addr_trans() {
	char *ipaddr = "163.13.132.68";
	int addr = inet_addr(ipaddr);
	if (addr == -1) {
		printf ("errno %d error desc: %s\n", errno, strerror(errno));
	}
	printf("%s inet_addr is %d \n", ipaddr, addr);

	struct in_addr net_addr;
	int addr_net = inet_aton(ipaddr, &net_addr);
	if (addr_net == -1) {
		printf ("errno %d error desc: %s\n", errno, strerror(errno));
	}
	printf("%s inet_aton is %d \n", ipaddr, net_addr.s_addr);

	char* addr_a = inet_ntoa(net_addr);
	printf("%d inet_ntoa is %s \n", net_addr.s_addr, addr_a);

	//inet_pton
	inet_pton(AF_INET, ipaddr, (void *)&net_addr);
	printf("%s inet_pton is %d \n", ipaddr, net_addr.s_addr);

	// inet_ntop
	char dest_addr[20];
	inet_ntop(AF_INET, &net_addr, dest_addr, sizeof(dest_addr));
	printf("%d inet_ntop is %s \n", net_addr.s_addr, dest_addr);
}

//SIGTERM信号处理，发现SIG_TERM 立即停止程序
//kill pid 发出的信号就是SIGTERM
static bool stop = false;
static void sig_term(int sig) {
	printf ("receive signal SIGTERM\n");
	stop = true;
}


//listen 测试函数
/**
从listen 开始创建监听队列，就可以接收连接，backlog指定连接最大数，超过此数，其他的连接请求不再接受，如下:
localhost:50581->localhost:search-agent (ESTABLISHED)
localhost:50735->localhost:search-agent (ESTABLISHED)
localhost:50738->localhost:search-agent (ESTABLISHED)
localhost:50739->localhost:search-agent (SYN_SENT)
localhost:50740->localhost:search-agent (SYN_SENT)
localhost:50740->localhost:search-agent (SYN_SENT)

*/
void accept_test(int socket);


void listen_test(int sockfd, int backlog) {

	int ret = listen(sockfd, backlog);
	assert(ret != -1);

	// while (!stop) {
		// printf("accept\n");
		// int sock = accept(sockfd, NULL, NULL);
		// printf("accept\n");
		// char *str = "ok";
		// send(sock, str, sizeof(str), 0);
		// sleep(1);
	// }
	accept_test(sockfd);

	close(sockfd);
}

void oobdata_test(int socket);
void getSockName(int sockfd);
/*
 accept 即使连接已经断开，accept 还是能够拿出连接队列
 *
*/
void accept_test(int socket) {
	// sleep(20) ;//测试断开连接后是否能accept
	struct sockaddr_in addr_in;
	socklen_t socklen = sizeof(addr_in);
	int sock = accept(socket, (struct sockaddr*)&addr_in, &socklen);
	if (sock < 0) {
		printf ("errno %d error desc: %s\n", errno, strerror(errno));
	} else {
		char remoteAddr[20];
		printf("connected success with ip:%s and port:%d\n", inet_ntop(AF_INET, &addr_in.sin_addr, remoteAddr, 20), ntohs(addr_in.sin_port));
		// sleep(10);
		getSockName(sock);
		oobdata_test(sock);
		close(sock);
	}
}

//近OOB数据的最后一个字符被当成带外数据接收，并且正常数据接收被截断。
//IO复用 MSG_URG信息
void oobdata_test(int connfd) {
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int ret = recv(connfd, buf, sizeof(buf), 0);
	printf("got %d bytes of normal data:%s\n", ret, buf);

	memset(buf, 0, sizeof(buf));
	ret = recv(connfd, buf, sizeof(buf), MSG_OOB);
	printf("got %d bytes of normal data:%s\n", ret, buf);

	memset(buf, 0, sizeof(buf));
	ret = recv(connfd, buf, sizeof(buf), 0);
	printf("got %d bytes of normal data:%s\n", ret, buf);
}

//获取本地域对端连接信息
void getSockName(int sockfd) {
	struct sockaddr_in serv, guest;
	socklen_t servlen, guestlen;
	getsockname(sockfd, (struct sockaddr *)&serv, &servlen);
	printf("getsockname is %s :%d \n",inet_ntoa(serv.sin_addr), ntohs(serv.sin_port));

	getpeername(sockfd, (struct sockaddr *)&guest, &guestlen);
	printf("getpeername is %s :%d \n",inet_ntoa(guest.sin_addr), ntohs(guest.sin_port));
}

//

int main(int argc, char *argv[]) {
	signal(SIGTERM, sig_term);
	printf("%s\n", argv[0]);
	if (argc < 3) {
		printf("usage %s ip_address ip_port backlog\n", basename(argv[0]));
		return 1;
	}

	// addr_trans();
    // return 0;

	const char *ip = argv[1];
	int port = atoi(argv[2]);
	int backlog = atoi(argv[3]);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd >=0);

	struct sockaddr_in addr_in;
	bzero(&addr_in, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port   = htons(port);
	// addr_in.sin_addr.s_addr = inet_addr("0.0.0.0");
	inet_pton(AF_INET, ip, &addr_in.sin_addr);

	printf("%s %d %d\n", ip, port, backlog);

	int ret = bind(sockfd, (struct sockaddr *)&addr_in, sizeof(addr_in));
	assert(ret != -1);

	listen_test(sockfd, backlog);


	// addr_trans();

	return 0;
}
