#ifndef __ATHREAD_H__
#define __ATHREAD_H__

#define THREAD_STACK_SIZE 10*1024*1024 //栈大小,10M

typedef enum workerStat {
    W_RUNNING,
    W_STOPING,
    W_STOP
} workerStat;

typedef struct threadWorker {
    int idx;// 在worker列表的索引位置
    pthread_t tid; //线程id
    int notify_read_fd;//master worker 线程通信管道读取端
    int notify_write_fd; //master worker 线程通信管道写端
    worker_stat_t status; //线程工作状态

    aeEventLoop   *ael; //ae句柄
    threadPool *pool; //线程池指针
    adlist *client_list; //本线程负责的client
    void *priv_data; //worker 自身数据
} threadWorker;

typedef struct threadPool {
    mutexLock *lock;

    threadWorker **thread_workers; //数组
    int threadWorkerNum; //线程数量

    int threadStackSize; //线程栈大小
    int clientTimeout; //client 超时时间
    int pollInterval; //worker线程cron频率
} threadPool;

threadPool *threadPoolCreate(int workerNum, int stackSize, void* (*workerTask)(void *arg));
int threadPollDestroy(threadPool *pool);
void *thread_worker_cycle(void *arg);
void threadSleep(int seconds);
void threadUnsleep(int useconds);
threadWorker *getWorker(int workerId);
void writeToClient(aeEventLoop *el, int fd, void *privdata, int mask);

#endif
