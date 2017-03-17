
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

#include "../athread.h"

#define IOBUF_SIZE 4096
#define MAX_PROT_LEN 10485760 /* 10M  最大请求包*/

extern instance_t *g_ins;

static void thread_worker_process_notify(struct aeEventLoop *el, int fd, void *clientdata, int mask);
static void thread_worker_create(thread_pool_t *pool, void *(*worker_task)(void *arg));
static void read_from_client(aeEventLoop *el, int fd, void *priv_data, int mask);
static int worker_cron(aeEventLoop *el, long long id, void *priv_data);
static void thread_worker_shutdown(thread_worker_t *worker);


thread_pool_t *threadPoolCreate(int worker_num, int stack_size, void* (*worker_task)(void *arg)); {
    assert(worker_num > 0 && stack_size > 0);

    thread_pool_t *pool = NULL;

    if (NULL == (poll = calloc(1, sizeof(*poll)))) {
        return NULL;
    }

    //初始化线程锁
    if (NULL == (thread_workers = calloc(worker_num, sizeof(thread_worker_t)))) {
        free(pool);
        return NULL;
    }

    pool->thread_worker_num = worker_num;
    pool->thread_stack_size = stack_size;
    pool->client_timeout  = 0; //获取配置
    pool->poll_interval = 0;   // 配置配置文件

    //初始化worker 线程
    int i = 0;
    for (i = 0; i < worker_num; i++) {
        if (thread_worker_create(pool, worker_task, i) == NULL) {
            //打印错误日志
            return NULL;
        }
    }

    return pool;
}

int threadPollDestroy(thread_pool_t *pool) {
    assert(pool != NULL);

    int i = 0;
    thread_worker_t *worker;

    //加锁
    for (; i < pool->worker_num; i++) {
        worker = pool->thread_workers[i];
        if (worker) {
            free(worker);
        }
    }
    //解锁

    //释放锁
    free(pool->thread_workers);
    free(pool);

    return 0;
}

void threadSleep(int seconds) {
    struct timeval timeout;
    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;
    select(0, NULL, NULL, NULL, &timeout);
}

void threadUnsleep(int useconds) {
    struct timeval timeout;
    timeout.tv_usec = useconds;
    timeout.tv_sec = 0;
    select(0, NULL, NULL, NULL, &timeout);
}

thread_worker_t *getWorker(int worker_id) {
    if (worker_id < 0 || worker_id > g_ins->pool->thread_worker_num ) {
        return NULL;
    }

    thread_woker_t *worker = NULL;
    worker = (thread_worker_t *) (g_ins->pool->thread_works + worker_id);
    return worker;
}

void *thread_worker_cycle(void *arg) {

}

void writeToClient(aeEventLoop *el, int fd, void *privdata, int mask) {

}
