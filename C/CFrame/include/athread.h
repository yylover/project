#ifndef __ATHREAD_H__
#define __ATHREAD_H__

#include "lock.h"
#include "ae.h"
#include "signal.h"
#include "adlist.h"

#define THREAD_STACK_SIZE 10*1024*1024 //栈大小,10M

//工作线程状态
typedef enum workerStat {
    WS_RUNNING,
    WS_STOPING,
    WS_STOPED
} workerStat;

typedef struct threadPool threadPool;

typedef struct threadWorker {
    pthread_t tid;       //线程id
    int idx;             // 在worker列表的索引位置
    threadPipeChannel *chan; //
    workerStat status;   //线程工作状态

    aeEventLoop   *ael; //ae句柄
    threadPool    *pool; //线程池指针
    list          *clientList; //本线程负责的client
    void          *priv_data; //worker 自身数据
} threadWorker;

struct threadPool {
    mutexLock *lock;

    threadWorker **threadWorkers; //数组
    int threadWorkerNum; //线程数量

    int threadStackSize; //线程栈大小
    int clientTimeout;   //client 超时时间
    int pollInterval;    //worker线程cron频率
} ;

threadPool *threadPoolCreate(int workerNum, int stackSize, void* (*workerTask)(void *arg));
int threadPollDestroy(threadPool *pool);
void *threadWorkerCycle(void *arg);
threadWorker *getWorker(threadPool *pool, int workerId);

void threadSleep(int seconds);
void threadUsecsleep(int useconds);

void writeToClient(aeEventLoop *el, int fd, void *privdata, int mask);

#endif
