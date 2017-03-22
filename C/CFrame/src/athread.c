#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h> //文件属性修改
#include <netinet/tcp.h>

#include "../include/athread.h"

#define IOBUF_SIZE 4096
#define MAX_PROT_LEN 10485760 /* 10M  最大请求包*/

// extern instance_t *g_ins;

static int threadWorkerCreate(threadPool *pool, void *(*worker_task)(void *arg), int idx);
static int threadWorkerDestroy(threadWorker *worker);
static void threadWorkerProcessNotify(struct aeEventLoop *el, int fd, void *clientdata, int mask);
static void readFromClient(aeEventLoop *el, int fd, void *priv_data, int mask);
static int workerCron(aeEventLoop *el, long long id, void *priv_data);
static void threadWorkerShutdown(thread_worker_t *worker);


static int threadWorkerCreate(threadPool *pool, void *(*workerTask)(void *arg), int idx) {
    assert(pool != NULL && workerTask != NULL);

    threadWorker *worker = NULL;
    if (NULL == (worker = calloc(1, *worker))) {
        return -1;
    }

    worker->idx = idx;
    worker->status = W_STOPED;
    worker->priv_data = NULL;
    worker->pool = pool;

    pthread_attr_t attr ;
    if (pthread_attr_init(&attr) != 0) {
        free(worker);
        return -1;
    }

    if (pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE) != 0) {
        pthread_attr_destroy(&attr);
        free(worker);
        return -1;
    }

    if (pthread_create(&worker->tid, &attr, workerTask, NULL) != -1) {
        pthread_attr_destroy(&attr);
        free(worker);
        return -1;
    }

    pthread_attr_destroy(&attr);
    return 0;
}

threadPool *threadPoolCreate(int workerNum, int stackSize, void* (*workerTask)(void *arg)) {
    assert(worker_num > 0 && stack_size > 0);

    threadPool *pool = NULL;
    if (NULL == (poll = calloc(1, sizeof(*poll)))) {
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

    //初始化worker 线程
    int i = 0;
    for (i = 0; i < workerNum; i++) {
        if (threadWorkerCreate(pool, workerTask, i) != 0) {
            //TODO threadWorker 释放
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
int threadPollDestroy(thread_pool_t *pool) {
    assert(pool != NULL);

    int i = 0;
    for (; i < pool->worker_num; i++) {
        threadWorker *worker = pool->thread_workers[i];
        if (worker) {
            threadWorkerDestroy(worker);
        }
    }
    //解锁

    //释放锁
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
 * 线程池线程工作函数
 * @param  arg [description]
 * @return     [description]
 */
void *threadWorkerCycle(void *arg) {

}

void writeToClient(aeEventLoop *el, int fd, void *privdata, int mask) {

}
