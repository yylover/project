#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "../include/master.h"
#include "../include/log.h"
#include "../include/anet.h"
#include "../include/signal.h"
#include "../include/athread.h"
#include "../include/afream.h"

extern instance_t *gInstance;

/**
 * 创建主线程
 * @param  listenfd     监听套接字fd
 * @param  clientLimit  连接数最大限制
 * @param  pollInterval 更新频率，用来判断client 是否已经断开链接
 * @return
 */
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
    master->clients = vectorCreate(clientLimit, sizeof(Client));
    master->eventloop = aeCreateEventloop(1024);
    pthreadMutexInit(master->lock);

    return master;
}

/**
 * 销毁主线程
 * @param master
 */
void destroyMaster(masterThread *master) {
    if (master) {
        vectorFree(master->clients);
        aeDeleteEventLoop(master->eventloop);
        pthreadMutexDestroy(master->lock);
    }

    free(master);
}

/**
 * 创建client连接
 * @param  clifd client fd
 * @param  ip    client ip
 * @param  port  client port
 * @return       0|-1
 */
int createClient(int clifd, const char *ip, int port) {
    Client *client = (Client*) malloc(sizeof(*client));
    if (client == NULL) {
        return -1;
    }

    memset(client, 0, sizeof(*client));
    client->fd = clifd;
    client->remoteIp = (char *)ip;
    client->remotePort = port;
    client->sendbuf = stringNewEmpty();
    client->recvbuf = stringNewEmpty();
    client->accessTime = time(NULL);

    client->idx = 0;       //clientVec 中位置
    client->workerId = 0; //工作线程id

    return 0;
}

/**
 * 清除Client 的存储空间
 * @param  client
 * @return
 */
int clientDestroy(Client *client) {
    if (client) {
        stringFree(client->recvbuf);
        stringFree(client->sendbuf);
    }
    free(client);
    return 0;
}


/**
 * 销毁client
 * @param eventloop
 * @param fd
 */
void closeClient(struct aeEventLoop *eventloop, int fd) {
    aeDeleteFileEvent(eventloop, fd, AE_READABLE);
    close(fd);
}

/**
 * 现在是低水平触发，如果不处理的话，要出发多次的
 * @param eventloop  时间循环
 * @param fd         文件描述符
 * @param clientData 线程数据
 * @param mask
 */
void handleReceive(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    char buf[1024];
    int nread = anetRead(fd, buf, 4);
    printf("data :%s %d\n", buf, nread);
    printf("handleReceive\n");
    if (nread == -1) {
        if (errno == EAGAIN) { //如果是非阻塞fd,如果没有内容，则errno=EAGAIN
            nread = 0;
        } else if (errno == EINTR) { //被打断
            nread = 0;
        } else {
            //其他错误关掉Client链接
            LOG_ERROR("Read connectin failed [:] interrupt :");
            closeClient(eventloop, fd);
            return ;
        }
    } else if (nread == 0) {
        //关掉链接
        closeClient(eventloop, fd);
        LOG_ERROR("Client connection closed");
        return ;
    }

    buf[nread] = '\0';
    //读取的内容拼接到接收缓冲区



}


/**
 * 接收连接
 * @param eventloop  [description]
 * @param fd         [description]
 * @param clientData [description]
 * @param mask       [description]
 */
void connectAccept(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    char err[ANET_ERR_LEN];
    char ip[128];
    int port = 0;
    int sock = anetTcpAccept(err, fd, ip ,sizeof(ip), &port);
    if (sock == ANET_ERR) {
        printf("create servr error :%s\n", err);
    }

    LOG_INFO("handleAccept %d %s %d\n", sock, ip, port);
    // anetNonBlock(NULL, sock);
    aeCreateFileEvent(eventloop, sock, AE_READABLE, handleReceive, clientData);
}

/**
 * 主线程关闭指令
 *
 *   1. 关闭listenfd
 *   2. 向所有worker线程发送关闭指令
 *   3. eventloop 退出
 */
void masterShutDown(masterThread *master) {

    //用户自定义析构函数

    //关闭listenfd, 程序会处于半连接状态，无法接收新的连接
    aeDeleteFileEvent(master->eventloop, master->listenfd, AE_READABLE);
    close(master->listenfd);

    //
    int i,info;
    threadWorker *worker = NULL;
    for (i = 0; i < gInstance->pool->threadWorkerNum; i++) {
        worker = *(gInstance->pool->threadWorkers+i);
        if (worker && worker->tid) {

            info = -1;
            int res = write(worker, &info, sizeof(int));
            if (res == -1) {
                LOG_ERROR("pipe write error :%d", errno);
                return ;
            }
        }
    }
    //UNLOCK

    threadUsecsleep(10*1000);

    do {
        int quitWorkers = 0;
        for (i = 0; i < gInstance->pool->threadWorkerNum; i++) {
            //判断连接状态


            quitWorkers ++;
        }

        if (quitWorkers <= 0) {
            break;
        } else {
            LOG_WARNING("Still not shutdown! (%d)", quitWorkers);
            threadUsecsleep(100 * 1000);
        }
    } while (1);

    //退出eventloop
    aeMainLoop(master->eventloop);

    LOG_INFO("master shut down");
    return ;

}


void handleSignalEvent(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    char buf[10];
    int nread = anetRead(fd, buf, 4);
    printf("signal :%s %d\n", buf, nread);

    if (nread != 4) {
        LOG_ERROR("master receive signal not errr:%s", buf);
        return;
    }

    masterThread *master = (masterThread *) clientData;
    if (strncpy(buf, "stop", 4) == 0) {
        master->status = STOPING;
        //通知所有的子线程
        masterShutDown(master);
    }
}


/**
 * 定时check 所有的client，如果有失效或断开的连接清除client信息
 *
 * @param  eventloop
 * @param  id         client id
 * @param  clientData
 * @return 周期秒数
 */
int  checkClients(struct aeEventLoop *eventloop, long long id, void *clientData) {
    masterThread *master = (masterThread *) clientData;

    LOG_INFO("checkClients");

    return 1000 * master->pollInterval;
}


/**
 * 主线程循环
 * @param listenfd     [description]
 * @param clientLimit  [description]
 * @param pollInterval [description]
 */
void masterCycle(int listenfd, int clientLimit, int pollInterval, threadPipeChannel * chan) {
    masterThread *master = createMaster(listenfd, clientLimit, pollInterval);
    if (NULL == master) {
        return;
    }

    //TODO 设置非阻塞 nodelay算法
    char err[ANET_ERR_LEN];
    if (anetNonBlock(err, listenfd) == ANET_ERR || anetEnableTcpNoDelay(err, listenfd) == ANET_ERR) {
        destroyMaster(master);
        return;
    }

    if (aeCreateFileEvent(master->eventloop, listenfd, AE_READABLE, connectAccept, NULL) != 0) {
        destroyMaster(master);
        return;
    }

    if (aeCreateTimeEvent(master->eventloop, 1000 *pollInterval, checkClients, master, NULL) != 0) {
        destroyMaster(master);
        return;
    }

    if (aeCreateFileEvent(master->eventloop, chan->readFd, AE_READABLE, handleSignalEvent, master) != 0) {
        destroyMaster(master);
        return ;
    }

    aeMainLoop(master->eventloop);

    destroyMaster(master);
}
