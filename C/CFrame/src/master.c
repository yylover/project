#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/master.h"
#include "../include/log.h"
#include "../include/anet.h"



masterThread *createMaster(int listenfd, int clientLimit, int pollInterval) {
    masterThread *master  = (masterThread *) malloc(sizeof(*master));
    if (NULL == master) {
        return NULL;
    }
    memset(master, 0, sizeof(*master));

    master->listenfd = listenfd;
    master->clientLimit = clientLimit;
    master->pollInterval = pollInterval;
    master->status = RUNNING;

    master->curConn = -1;
    master->curThread = 0;
    master->totalClients = 0;
    master->clients = vectorCreate(32, sizeof(Client));
    master->eventloop = aeCreateEventloop(1024);

    return master;
}

void destroyMaster(masterThread *master) {
    if (master) {
        vectorFree(master->clients);
        aeDeleteEventLoop(master->eventloop);
    }

    free(master);
}

void handleReceive(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    char buf[1024];
    int t = anetRead(fd, buf, 4);
    printf("data :%s %d\n", buf, t);

    printf("handleReceive\n");
}

void connectAccept(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    char err[ANET_ERR_LEN];
    char ip[128];
    int port = 0;
    int sock = anetTcpAccept(err, fd, ip ,sizeof(ip), &port);
    if (sock == ANET_ERR) {
        printf("create servr error :%s\n", err);
    }

    LOG_INFO("handleAccept %d %s %d\n", sock, ip, port);
    anetNonBlock(NULL, sock);
    aeCreateFileEvent(eventloop, sock, AE_READABLE, handleReceive, clientData);
}



int  checkClients(struct aeEventLoop *eventloop, long long id, void *clientData) {
    return 0;
}


void masterCycle(int listenfd, int clientLimit, int pollInterval) {



    masterThread *master = createMaster(listenfd, clientLimit, pollInterval);
    if (NULL == master) {
        return;
    }

    if (aeCreateFileEvent(master->eventloop, listenfd, AE_READABLE, connectAccept, NULL) != 0) {
        return;
    }

    if (aeCreateTimeEvent(master->eventloop, 1000 *pollInterval, checkClients, NULL, NULL) != 0) {
        return;
    }

    aeMainLoop(master->eventloop);

    destroyMaster(master);
}
