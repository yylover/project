#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>

#include "../include/signal.h"
#include "../include/log.h"
#include "../include/anet.h"

#define DUMP_STACK_DEPTH_MAX 16

/**


struct sigaction :
    * sa_flags:
        * SA_SIGINFO:void (*sa_handler)(int) 或 void(*sa_sigaction)(int,siginfo_t *, void *) 使用哪一个处理函数
        * SA_RESETHAND:当调用信号处理函数时，则系统调用自动
        * SA_RESTART: 如果信号中断了进程的某个系统调用，则系统自动启动原来的调用。
        * SA_NODEFER: 一般情况下，信号处理函数执行时，内核将阻塞该信号，设置之后，内核不阻塞该信号
        * SA_ONSTACK: 如果设置了，并使用signalstack()或sigstack() 声明了备用信号堆栈，信号将传递给该调用堆栈中的调用进程，否则信号在当前堆栈上传递。
    * sa_handler: 信号处理函数
 */

signalInfo signalinfos[] = {
    {SIGTERM, "SIGTERM"},
    {SIGQUIT, "SIGQUIT"},
    {SIGCHLD, "SIGCHLD"},
    {SIGPIPE, "SIGPIPE"},
    {SIGINT, "SIGINT"},
    {SIGSEGV, "SIGSEGV"},
    {SIGBUS, "SIGBUS"},
    {SIGFPE, "SIGFPE"},
    {SIGILL, "SIGILL"},
    {SIGHUP, "SIGHUP"},
    {0, NULL},
};


char * getSignalName(int signo) {
    signalInfo *head = signalinfos;
    for (; head->signo != 0; head++) {
        if (head->signo == signo) {
            return head->signame;
        }
    }
    return NULL;
}

/**
 * 公共信号处理函数
 *
 *
 * @param signo 信号
 * @param chan
 */
static void publicSignalHandler(int signo, threadPipeChannel *chan) {

    char *signame = getSignalName(signo);
    if (signame) {
        LOG_INFO("Thread[%lu] receive signal:%s", pthread_self(), signame);
    } else {
        LOG_INFO("Thread[%lu] receive unexpect signal:%d", pthread_self(), signo);
    }

    int stop = 0;
    switch (signo) { //直接退出
        case SIGQUIT:
        case SIGTERM:
        case SIGINT:
            stop = 1;
            break;
        case SIGPIPE://不处理
        case SIGCHLD:
        case SIGHUP:
            break;
    }

    char *stopStr = "stop";
    if (stop) {
        if (write(chan->writeFd, stopStr, strlen(stopStr)) != 4) {
            if (errno == EINTR) {
                LOG_INFO("Worker thread[ signal] quit");
                write(chan->writeFd, stopStr, strlen(stopStr));
                pthread_exit(0);
            } else {
                LOG_ERROR("PIPE write error: %s", strerror(errno));
            }

        } else {
            LOG_INFO("Worker thread[ signal] quit");
            pthread_exit(0);
        }
    }
}

/**
 * 私有信号处理函数
 * @param signo  信号
 * @param info   外带参数
 * @param secret
 */
static void privateSignalHandler(int signo) {
    //打印栈信息

    void *stackTrace[DUMP_STACK_DEPTH_MAX];
    int traceDepth = backtrace(stackTrace, DUMP_STACK_DEPTH_MAX); //调用深度

    char ** stackString = (char **) backtrace_symbols(stackTrace, traceDepth);
    if (NULL == stackString) {
        LOG_ERROR("Print log trace failed: %s", strerror(errno));
        return ;
    }

    LOG_INFO("----Stack trace begin -----");
    int i ;
    for (i = 0; i < traceDepth; i++) {
        LOG_INFO("[%d] %s \r\n", i, stackTrace[i]);
    }
    free(stackString);
    stackString = NULL;
    LOG_INFO("----Stack trace end -----");

    //传给系统，用默认方式处理该信号
    struct sigaction sa;
    sa.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
    sa.sa_handler = SIG_DFL;
    sigaction(signo, &sa, NULL);
    raise(signo);
}

static void* signalThreadCycle(void *privData) {
    sigset_t bset;
    // siginfo_t info;
    int signo;

    sigemptyset(&bset);
    sigaddset(&bset, SIGTERM); // 终止进程
    sigaddset(&bset, SIGHUP);  // 终端挂起或控制进程终止
    sigaddset(&bset, SIGQUIT); // 键盘退出指令
    sigaddset(&bset, SIGCHLD); // 子进程结束
    sigaddset(&bset, SIGPIPE); // 管道错误
    sigaddset(&bset, SIGINT); // 键盘中断

    while (1) {
        //阻塞等待信号
        int rc = sigwait(&bset, &signo);
        // int rc = sigwaitinfo(&bset, &info);
        if (rc != -1) {
            //处理信号
            publicSignalHandler(signo, (threadPipeChannel *)privData);
        } else {
            LOG_ERROR("sigwaitinfo return error:%s", strerror(errno));
        }
    }
    return NULL;
}

/**
 * 创建threadPipeChannel
 * @return [description]
 */
threadPipeChannel * createThreadPipeChannel() {
    threadPipeChannel* chan = (threadPipeChannel*) malloc(sizeof(*chan));
    if (chan == NULL) {
        return NULL;
    }

    int fds[2];
    if (pipe(fds) != 0) {
        free(chan);
        return NULL;
    }

    chan->readFd = fds[0];
    chan->writeFd = fds[1];

    //设置非阻塞 TODO
    if (0 != anetNonBlock(NULL, fds[0]) || 0 != anetNonBlock(NULL, fds[1])) {
        free(chan);
        return NULL;
    }

    return chan;
}

/**
 * 释放threadPipeChannel
 * @param chan [description]
 */
void destroyThreadPipeChannel(threadPipeChannel *chan) {
    if (chan) {
        close(chan->readFd);
        close(chan->writeFd);
        free(chan);
    }
}

/**
 * 私有信号处理
 *
 * 主要对程序bug发生时,打印栈信息
 * @return [description]
 */
int handlePrivateSignals() {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask); //清空所有信号

    sa.sa_flags = SA_RESETHAND | SA_SIGINFO | SA_RESTART;
    sa.sa_handler = privateSignalHandler;

    sigaction(SIGSEGV, &sa, NULL);// 段错误
    sigaction(SIGBUS, &sa, NULL); // 总线错误，非法地址，包括内存对齐出错
    sigaction(SIGFPE, &sa, NULL); // 浮点数错误
    sigaction(SIGILL, &sa, NULL); // 非法指令错误

    return 0;
}

/**
 * 创建公共信号处理
 * @param  chan 信号发生时要发送的管道
 * @return
 */
int handlePublicSignals(threadPipeChannel *chan) {
    sigset_t bset, oset;

    //阻塞信号
    sigemptyset(&bset);
    sigaddset(&bset, SIGTERM); // 终止进程
    sigaddset(&bset, SIGHUP);  // 终端挂起或控制进程终止
    sigaddset(&bset, SIGQUIT); // 键盘退出指令
    sigaddset(&bset, SIGCHLD); // 子进程结束
    sigaddset(&bset, SIGPIPE); // 管道错误
    sigaddset(&bset, SIGINT); // 键盘中断

    if (pthread_sigmask(SIG_BLOCK, &bset, &oset) != 0) {
        LOG_ERROR("set pthread sigmask failed %s", strerror(errno));
        return -1;
    }

    pthread_t      ppid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&ppid, &attr, signalThreadCycle, chan);
    pthread_attr_destroy(&attr);

    return 0;
}
