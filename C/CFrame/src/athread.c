#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h> //文件属性修改
#include <netinet/tcp.h>

#include "../include/athread.h"
#include "../include/log.h"
#include "../include/adlist.h"
#include "../include/string.h"
#include "../include/master.h"
#include "../include/adlist.h"
#include "../include/afream.h"

#define IOBUF_SIZE 4096
#define MAX_PROT_LEN 10485760 /* 10M  最大请求包*/

extern instance_t *gInstance;

static int threadWorkerCreate(threadPool *pool, void *(*workerTask)(void *arg), int idx);
static int threadWorkerDestroy(threadWorker *worker);
static void threadWorkerProcessNotify(struct aeEventLoop *el, int fd, void *clientdata, int mask);
static void readFromClient(aeEventLoop *el, int fd, void *priv_data, int mask);
// static int workerCron(aeEventLoop *el, long long id, void *priv_data);
static void threadWorkerShutdown(threadWorker *worker);


/**
 * 创建工作线程
 * @param  pool       线程池句柄
 * @param  workerTask 线程工作函数
 * @return
 */
static int threadWorkerCreate(threadPool *pool, void *(*workerTask)(void *arg), int idx) {
    assert(pool != NULL && workerTask != NULL);

    threadWorker *worker = NULL;
    if (NULL == (worker = calloc(1, sizeof(*worker)))) {
        return -1;
    }

    worker->idx = idx;
    worker->status = WS_STOPED;
    worker->priv_data = NULL;
    worker->pool = pool;
    if (NULL == (worker->chan = createThreadPipeChannel())) {
        free(worker);
        return -1;
    }

    if (NULL == (worker->ael = aeCreateEventloop(1024))) {
        destroyThreadPipeChannel(worker->chan);
        free(worker);
        return -1;
    }

    if (!(worker->clientList = listCreate())) {
        aeDeleteEventLoop(worker->ael);
        destroyThreadPipeChannel(worker->chan);
        free(worker);
        return -1;
    }

    pthread_attr_t attr ;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&worker->tid, &attr, workerTask, NULL) != 0) {
        aeDeleteEventLoop(worker->ael);
        destroyThreadPipeChannel(worker->chan);
        pthread_attr_destroy(&attr);
        free(worker);
        return -1;
    }

    pthread_attr_destroy(&attr);
    return 0;
}

int threadWorkerDestroy(threadWorker *worker) {
    //停止线程循环
    worker->pool = NULL;
    aeStop(worker->ael);
    listRelease(worker->clientList);
    aeDeleteEventLoop(worker->ael);
    destroyThreadPipeChannel(worker->chan);
    free(worker);
    return 0;
}

/**
 * 线程池创建
 * @param  workerNum  工作线程数
 * @param  stackSize  栈大小
 * @param  workerTask 工作线程函数
 * @return            NULL| threadPool *
 */
threadPool *threadPoolCreate(int workerNum, int stackSize, void* (*workerTask)(void *arg)) {
    assert(workerNum > 0 && stackSize > 0);

    threadPool *pool = NULL;
    if (NULL == (pool = calloc(1, sizeof(*pool)))) {
        return NULL;
    }

    if (NULL == (pool->threadWorkers = calloc(workerNum, sizeof(threadWorker)))) {
        free(pool);
        return NULL;
    }

    pool->threadWorkerNum = workerNum;
    pool->threadStackSize = stackSize;
    pool->clientTimeout   = 10; //获取配置
    pool->pollInterval    = 10; // 配置配置文件

    pthreadMutexInit(pool->lock);

    //初始化worker 线程
    int i = 0;
    for (i = 0; i < workerNum; i++) {
        if (threadWorkerCreate(pool, workerTask, i) != 0) {
            //TODO threadWorker 释放
            LOG_INFO("worker init failed");
            pthreadMutexDestroy(pool->lock);
            free(pool);
            return NULL;
        }
    }

    return pool;
}

/**
 * 线程池销毁函数
 * @param  pool [description]
 * @return      [description]
 */
int threadPollDestroy(threadPool *pool) {
    assert(pool != NULL);

    int i = 0;
    pthreadMutexLock(pool->lock);
    for (; i < pool->threadWorkerNum; i++) {
        threadWorker *worker = pool->threadWorkers[i];
        if (worker) {
            threadWorkerDestroy(worker);
        }
    }
    pthreadMutexUnlock(pool->lock);

    pthreadMutexDestroy(pool->lock);
    free(pool->threadWorkers);
    free(pool);

    return 0;
}

/**
 * 线程休眠秒数
 * @param seconds
 */
void threadSleep(int seconds) {
    struct timeval timeout;
    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;
    select(0, NULL, NULL, NULL, &timeout);
}

/**
 * 线程休眠毫秒数
 * @param useconds
 */
void threadUsecsleep(int useconds) {
    struct timeval timeout;
    timeout.tv_usec = useconds;
    timeout.tv_sec = 0;
    select(0, NULL, NULL, NULL, &timeout);
}

/**
 * 获取工作线程
 * @param  worker_id [description]
 * @return           [description]
 */
threadWorker *getWorker(threadPool *pool, int workerId) {
    if (workerId < 0 || workerId > pool->threadWorkerNum ) {
        return NULL;
    }

    return (threadWorker *) (pool->threadWorkers + workerId);
}

/**
 * 向client write response
 * @param eventloop  事件循环
 * @param fd         文件描述符
 * @param clientData client数据
 * @param mask
 */
void WriteClientReaponse(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    Client *client = (Client *) clientData;

    int nwrite = write(fd, client->sendbuf->buf, client->sendbuf->len);
    client->accessTime = time(NULL);
    if (nwrite < 0) {
        if (errno == EAGAIN) {
            nwrite = 0;
        } else if (errno == EINTR) {
            nwrite = 0;
        } else {
            // closeClient
            return ;
        }
    }

    LOG_INFO("write to client %s:%d writeLen:%d", client->remoteIp, client->remotePort, nwrite);

    if (0 != stringRange(client->sendbuf, nwrite, client->sendbuf->len -1)) {
        stringClear(client->sendbuf);
    }

    if (client->sendbuf->len == 0) {
        aeDeleteFileEvent(eventloop, fd, AE_WRITABLE);
        if (client->closeConn) {
            //TODO closeClient
        }
    }
}

/**
 * client 有可读事件时回调，读取client数据
 * @param eventloop  [description]
 * @param fd         [description]
 * @param clientData [description]
 * @param mask       [description]
 */
void handleClientData(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    Client *client = (Client*) clientData;

    int nread;
    char buf[IOBUF_SIZE];
    int ret;

    nread = read(fd, buf, IOBUF_SIZE-1);
    if (nread == -1) {
        if (errno == EAGAIN) { //非阻塞fd,无内容可读时返回-1,errno=EAGAIN
            nread = 0;
            return;
        } else if (errno == EINTR) {
            LOG_WARNING("Read connection [%s:%d] interrupt :%s", client->remoteIp, client->remotePort, strerror(errno));
            nread = 0;
            return ;
        } else {
            //TODO 关闭连接
            return ;
        }
    } else if (nread == 0) {
        //TODO close connection
        return ;
    }
    buf[nread] = '\0';

    stringCat(&client->recvbuf, buf);
    while (client->recvbuf->len > 0) {
        if (client->recvProtoLen == 0) {
            // client->recvProtoLen = gInstance->
            LOG_INFO("Get protolen ;%d for connection:%s %d", client->recvProtoLen, client->remoteIp, client->remotePort);
            return ;
        }

        if (client->recvProtoLen < 0 || client->recvProtoLen > MAX_PROT_LEN) {
            LOG_INFO("invalid protocol lenth:%d", client->recvProtoLen);
            closeClientByIndx(client->idx, "wrong recv proto len");
            return ;
        }

        if (client->recvProtoLen == 0) {
            client->status = RECEIVING;
            return ;
        }

        if (client->recvbuf->len >= client->recvProtoLen) {
            client->status = PROCESSING;
            // ret = gInstance->soFuns->handleProcess(client);
            int ret = 0;
            if (ret == 0) {
                LOG_INFO("handle process success, connection :%s %d", client->remoteIp, client->remotePort);
            } else if (-4 == ret) {
                client->closeConn = 1; //response 成功之后，自动关闭连接
                aeDeleteFileEvent(eventloop, fd, AE_READABLE);
            } else {
                //处理失败
                LOG_ERROR("the handle process failed:connection:%s %d", client->remoteIp, client->remotePort);
                return ;
            }

            //协议长度清空，因为每次请求都是独立的，请求的协议长度随时可能发生变化，比如httpd 服务器，因此需要随机计算
            client->recvProtoLen = 0;
            client->status = WAITING;

            if (client->sendbuf->len > 0) {
                threadWorker *worker = getWorker(gInstance->pool, client->workerId);
                if (aeCreateFileEvent(worker->ael, client->fd, AE_WRITABLE, WriteClientReaponse, client) == -1) {
                    // closeClient();
                    LOG_ERROR("create write file event failed: connection:%s %d", client->remoteIp, client->remotePort);
                    return ;
                }
            }
        } else {
            //
            return;
        }
    }
}

/**
 * 监听管道命令
 *
 * 退出命令-1 其他是分配的client fd 数字
 * @param eventloop  事件循环
 * @param fd         文件描述符
 * @param clientData 用户数据
 * @param mask
 */
void handlePipeEvent(struct aeEventLoop *eventloop, int fd, void *clientData, int mask) {
    threadWorker *worker = (threadWorker *) clientData;

    int readLen=0, clientIdx=0;
    if ((readLen = read(fd, &clientIdx, sizeof(int))) != sizeof(int)) {
        LOG_ERROR("Worker [%d] read notify_fd failed: %d", worker->idx, readLen);
        return ;
    }

    if (-1 == clientIdx) { //退出信号
        threadWorkerShutdown(worker);
        return;
    }
    pthreadMutexLock(gInstance->lock);
    Client *client = vectorGetAt(gInstance->master->clients, clientIdx);
    pthreadMutexUnlock(gInstance->lock);
    if (client) {
        LOG_ERROR("worker[%d] get the client error, idx :%d", worker->idx, clientIdx);
        return ;
    }

    client->workerId = worker->idx;
    client->status  = WAITING;

    //添加新的事件描述符
    listAddNodeTail(worker->clientList, client);

    //TODO handleOpen() client新打开时发送欢迎信息

    if (aeCreateFileEvent(worker->ael, client->fd, AE_READABLE, handleClientData, client) == -1) {
        //closeClient;
        LOG_ERROR("create file fd event failed: %s %d", client->remoteIp, client->remotePort);
        return ;
    }
}

int handleCronEvent(struct aeEventLoop *eventloop, long long id, void *clientData) {
    threadWorker *worker = (threadWorker *)clientData;

    listIter *iter = listGetIterator(worker->clientList, AL_START_HEAD);
    time_t unixClock = time(NULL); //当前时间
    listNode *node = NULL;
    Client *client = NULL;

    while ((node = listNext(iter))) {
        client = node->value;
        if (unixClock - client->accessTime > worker->pool->clientTimeout) {

            //TODO close
        }
    }

    LOG_INFO("worker[%d] cron end. Client count:%d", worker->idx, worker->clientList->length);

    return 1000 * gInstance->pool->pollInterval;
}


/**
 * 线程池线程工作函数
 * @param  arg [description]
 * @return     [description]
 */
void *threadWorkerCycle(void *arg) {
    threadWorker *worker = (threadWorker *) arg;
    worker->status = WS_RUNNING;

    //TODO handlerWorkerInit() 线程初始化函数调用

    if (aeCreateFileEvent(worker->ael, worker->chan->readFd, AE_READABLE, handlePipeEvent, arg) != 0) {
        return NULL;
    }

    if (0 != aeCreateTimeEvent(worker->ael, 1000*gInstance->pool->pollInterval, handleCronEvent, arg, NULL)) {
        return NULL;
    }

    aeMainLoop(worker->ael);

    worker->tid = 0;
    worker->idx = -1;
    // TODO handleWorkerDeinit() 线程终结回调函数
    pthread_exit(0);
    return NULL;
}

void threadWorkerShutdown(threadWorker *worker) {
    worker->status = WS_STOPING;
    listNode *node = NULL;

    Client *client = NULL;
    listIter *iter = listGetIterator(worker->clientList, AL_START_HEAD);
    while ((node = listNext(iter))) {
        client = node->value;
        //CLOSE connect
    }

    LOG_INFO("worker[%d] end shutdown", worker->chan->readFd, AE_READABLE);

}

// void writeToClient(aeEventLoop *el, int fd, void *privdata, int mask) {

// }
