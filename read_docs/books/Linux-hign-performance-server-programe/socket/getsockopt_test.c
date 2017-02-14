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
#include <errno.h>
#include <assert.h>

/*
 * This function report the error and
 * exits back to the shell:
 */
static void bail(const char *on_what)
{
    if(errno != 0)
    {
    fputs(strerror(errno),stderr);
    fputs(": ",stderr);
    }
    fputs(on_what,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char **argv)
{
    int z;
    int s=-1;            /* Socket */
    int sndbuf=0;        /* Send buffer size */
    int rcvbuf=0;        /* Receive buffer size */
    socklen_t optlen1, optlen2;        /* Option length */

    /*
     * Create a TCP/IP socket to use:
     */
    s = socket(AF_INET,SOCK_STREAM,0);
    if(s==-1)
    bail("socket(2)");

    int len = 65536;
    setsockopt(s, SOL_SOCKET, SO_SNDBUF, &len, sizeof(len));
    int yes = 2;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    /*
     * Get socket option SO_SNDBUF:
     */
    optlen1 = sizeof sndbuf;
    z = getsockopt(s,SOL_SOCKET,SO_SNDBUF,&sndbuf,&optlen1);

    if(z)
    bail("getsockopt(s,SOL_SOCKET,"
        "SO_SNDBUF)");

    assert(optlen1 == sizeof sndbuf);

    /*
     * Get socket option SON_RCVBUF:
     */

    optlen2 = sizeof rcvbuf;
    z = getsockopt(s,SOL_SOCKET,SO_RCVBUF,&rcvbuf,&optlen2);
    if(z)
    bail("getsockopt(s,SOL_SOCKET,"
        "SO_RCVBUF)");

    assert(optlen2 == sizeof rcvbuf);

    /*
     * Report the buffer sizes:
     */
    printf("Socket s: %d\n",s);
    printf("Send buf: %d bytes %d \n",sndbuf, optlen1);
    printf("Recv buf: %d bytes %d \n",rcvbuf, optlen2);

    int value = -1;
    z = getsockopt(s,SOL_SOCKET,SO_REUSEADDR,&value,&optlen2);
    printf("Recv buf: %d bytes %d \n",value, optlen2);

    close(s);
    return 0;
}
