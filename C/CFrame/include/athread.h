#ifndef __ATHREAD_H__
#define __ATHREAD_H__

#include "lock.h"

#define THREAD_STACK_SIZE 10*1024*1024 //栈大小,10M

typedef enum workerStat {
    W_RUNNING,
    W_STOPING,
    W_STOPED
} workerStat;

struct threadPool;

typedef struct threadWorker {

    pthread_t tid;       //线程id
    int notify_read_fd;  //master worker 线程通信管道读取端
    int notify_write_fd; //master worker 线程通信管道写端
    workerStat status;   //线程工作状态
    int idx;             // 在worker列表的索引位置

    aeEventLoop   *ael; //ae句柄
    threadPool    *pool; //线程池指针
    adlist        *client_list; //本线程负责的client
    void          *priv_data; //worker 自身数据
} threadWorker;

typedef struct threadPool {
    mutexLock *lock;

    threadWorker **threadWorkers; //数组
    int threadWorkerNum; //线程数量

    int threadStackSize; //线程栈大小
    int clientTimeout;   //client 超时时间
    int pollInterval;    //worker线程cron频率
} threadPool;

threadPool *threadPoolCreate(int workerNum, int stackSize, void* (*workerTask)(void *arg));
int threadPollDestroy(threadPool *pool);
void *threadWorkerCycle(void *arg);
threadWorker *getWorker(int workerId);

void threadSleep(int seconds);
void threadUsecsleep(int useconds);

void writeToClient(aeEventLoop *el, int fd, void *privdata, int mask);

#endif
