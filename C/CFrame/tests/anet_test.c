#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <google/cmockery.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h> //close()

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
    assert_int_equal(value, 4);

    //
    close(sock);

    char err[256];
    // anetTcpServer(buf, 8000, "127.0.0.1", 5);

}



int main(int argc, char* argv[]) {
    const UnitTest tests[] = {
        unit_test(test_setError),
    };
    return run_tests(tests);
}
