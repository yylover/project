#include "../include/ae.h"
#include "../include/anet.h"
#include <string.h>
#include <stdio.h>

typedef struct privData {
    char buf[123];
} privData;


int  aeTimeProc1 (struct aeEventLoop *eventloop, long long id, void *clientData) {
    privData *d = (privData *) clientData;
    printf("this is timer :%s\n", d->buf);

    return 1000;
}

int  aeTimeProc2 (struct aeEventLoop *eventloop, long long id, void *clientData) {
    privData *d = (privData *) clientData;
    // printf("this is timer :%s\n", d->buf);

    return 2000;
}

int  aeTimeProc3 (struct aeEventLoop *eventloop, long long id, void *clientData) {
    privData *d = (privData *) clientData;
    // printf("this is timer :%s\n", d->buf);

    return -1;
}

void aeEventFinalizerProc1(struct aeEventLoop *eventloop, void *clientData) {
    privData *d = (privData *) clientData;
    // printf("aeEventFinalizerProc timer :%s\n", d->buf);
}

void aeBeforeSleepProc1(struct aeEventLoop *eventloop) {
    // printf("aeBeforeSleepProc\n");
}

void handleReceive(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    char buf[1024];
    int t = anetRead(fd, buf, 4);
    printf("data :%s %d\n", buf, t);

    printf("handleReceive\n");
}

void handleAccept(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    char err[ANET_ERR_LEN];
    char ip[128];
    int port = 0;
    int sock = anetTcpAccept(err, fd, ip ,sizeof ip, &port);
    if (sock == ANET_ERR) {
        printf("create servr error :%s\n", err);
    }

    printf("handleAccept %d %s %d\n", sock, ip, port);
    anetNonBlock(NULL, sock);
    aeCreateFileEvent(eventloop, sock, AE_READABLE, handleReceive, clientData);
}



int main() {

    privData d1, d2, d3;
    strcpy(d1.buf, "time1");
    strcpy(d2.buf, "time2");
    strcpy(d3.buf, "time3");

    aeEventLoop *eventloop = aeCreateEventloop(1024);
    aeSetBeforeSleepProc(eventloop, aeBeforeSleepProc1);

    aeCreateTimeEvent(eventloop, 1000, aeTimeProc1, &d1, aeEventFinalizerProc1);
    aeCreateTimeEvent(eventloop, 2000, aeTimeProc2, &d2, aeEventFinalizerProc1);
    aeCreateTimeEvent(eventloop, 2000, aeTimeProc3, &d3, aeEventFinalizerProc1);

    char err[ANET_ERR_LEN];
    int listenSock = anetTcpServer(err, 8000, "127.0.0.1", 5);
    if (listenSock == ANET_ERR) {
        printf("create servr error :%s\n", err);
    }

    anetNonBlock(NULL, listenSock);
    aeCreateFileEvent(eventloop, listenSock, AE_READABLE, handleAccept, NULL);


    aeMainLoop(eventloop);
    aeDeleteEventLoop(eventloop);

    return 0;
}
