#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <google/cmockery.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h> //close()
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/tcp.h>

#include "../include/adlist.h"
#include "../include/anet.h"


void test_setError(void **state) {
    char buf[128];

    //
    anetSetError(buf, "This is %s and %d", "yang", 156);
    assert_string_equal(buf, "This is yang and 156");

    //创建socket
    int sock = anetTcpServer(NULL, 8000, "127.0.0.1", 5);
    assert_true(sock > 2);

    //判断是否SO_REUSEADDR选项是否生效
    int value = 0;
    socklen_t valueLen = sizeof value;
    int res = getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &value, &valueLen);
    assert_true(value);

    //TcpNodelay测试
    res = anetEnableTcpNoDelay(NULL, sock);
    value = 0;
    res = getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &value, &valueLen);
    assert_true(value);
    res = anetDisableTcpNoDelay(NULL, sock);
    res = getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &value, &valueLen);
    assert_int_equal(0, value);

    //keepalive 测试
    res = anetTcpKeepAlive(NULL, sock);
    assert_int_equal(res, 0);
    res = getsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &value, &valueLen);
    assert_true(value);

    //sendtimeout
    anetSendTimeout(NULL, sock, 22008);
    struct timeval tv;
    socklen_t timeLen = sizeof tv;
    res = getsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, &timeLen);
    assert_int_equal(res, 0);
    assert_int_equal(tv.tv_sec, 22);
    assert_int_equal(tv.tv_usec, 8000);
    printf("%ld %d\n", tv.tv_sec, tv.tv_usec);


    //accept test
    char ip[128];
    int port = 0;
    res = anetTcpAccept(NULL, sock, ip, sizeof(ip), &port);
    assert_int_equal(res, 0);
    assert_string_equal("127.0.0.1", ip);
    printf("%s %d\n", ip, port);

    //阻塞和非阻塞判断
    anetNonBlock(NULL, sock);
    int flags = fcntl(sock, F_GETFL);
    assert_true((flags & O_NONBLOCK) == O_NONBLOCK);
    res = anetBlock(buf, sock);
    flags = fcntl(sock, F_GETFL);
    assert_true((flags & O_NONBLOCK) == 0);

    //
    close(sock);

    char err[256];
    // anetTcpServer(buf, 8000, "127.0.0.1", 5);

}

void test_anetTcpAccept(void **state) {
}


int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_setError),
    };
    return run_tests(tests);
}
