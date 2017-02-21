#ifndef __ATHREAD_H__
#define __ATHREAD_H__

#define THREAD_STACK_SIZE 10*1024*1024 //栈大小,10M

typedef enum worker_stat {
    W_RUNNING,
    W_STOPING,
    W_STOP
} worker_stat_t;

typedef struct thread_worker {
    int idx;// 在worker列表的索引位置
    pthread_t tid; //线程id
    int notify_read_fd;//master worker 线程通信管道读取端
    int notify_write_fd; //master worker 线程通信管道写端
    worker_stat_t status; //线程工作状态

    aeEventLoop *t_ael; //ae句柄
    thread_pool_t *pool; //线程池指针
    adlist *client_list; //本线程负责的client
    void *priv_data; //worker 自身数据


} thread_worker;

typedef struct thread_pool {
    lock_t *thread_lock;
    thread_worker_t **thread_workers;

    int thread_worker_num; //线程数量
    int thread_stack_size; //栈大小

    int client_timeout; //client 超时时间
    int poll_interval; //worker线程cron频率
} thread_pool_t;

thread_pool_t *threadPoolCreate(int worker_num, int stack_size, void* (*worker_task)(void *arg));
int threadPollDestroy(thread_pool_t *pool);
void *thread_worker_cycle(void *arg);
void threadSleep(int seconds);
void threadUnsleep(int useconds);
thread_worker_t *getWorker(int worker_id);
void writeToClient(aeEventLoop *el, int fd, void *privdata, int mask);

#endif
