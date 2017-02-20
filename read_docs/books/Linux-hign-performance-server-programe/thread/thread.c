#include <pthread.h>

#include <bits/pthreadtypes.h>
typedef unsigned long int pthread_t;
/**
 * 创建一个线程
 * @param  thread        指向pthread_create类型的指针，用于引用新创建的线程。
 * @param  attr          用于设置线程的属性，默认属性可以设置为NULL。
 * @param  start_routine 传递新线程所要执行的函数地址。
 * @param  arg           新线程所要执行的函数的参数。
 * @return               0 成功， 错误码
 */
int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

/**
 * 线程退出函数，可以保证安全、干净的退出。
 *
 * 线程通过调用pthread_exit函数终止执行，并返回一个指向某对象的指针。注意：绝不能用它返回一个指向局部变量的指针，因为线程调用该函数后，这个局部变量就不存在了，这将引起严重的程序漏洞。
 * @param retval 返回指针，指向线程向要返回的某个对象。
 */
void pthread_exit(void *retval);

/**
 * 回收线程，阻塞执行（前提是目标进程可回收）
 * @param  th            线程标识
 * @param  thread_return 目标线程返回的退出信息
 * @return               0，成功；失败返回错误码
 */
int pthread_join(pthread_t th, void **thread_return);

/**
 * 异常终止一个线程，取消线程
 * @param  thread 线程标识
 * @return        0成功 失败返回错误码
 */
int pthread_cancel(pthread_t thread);

/**
 * 设置线程的取消状态
 * @param  state    PTHREAD_CANCEL_ENABLE | PTHREAD_CANCEL_DISABLE 是否允许取消
 * @param  oldstate
 * @return
 */
int pthread_setcancelstate(int state, int *oldstate);

/**
 * 设置线程的取消类型
 * @param  type    PTHREAD_CANCEL_ASYNCHRONOUS 线程随时可以取消
 *                 PTHREAD_CANCEL_DEFERRED 允许线程推迟行动。
 * @param  oldtype 原来的值
 * @return         成功返回0，失败错误码
 */
int pthread_setcanceltype(int type, int *oldtype);


bool daemonize() {
    /** 创建子进程，父进程退出**/
    pid_t pid = fork();
    if (pid < 0) {
        return false;
    } else if (pid > 0) {
        exit(0);
    }

    /*设置文件掩码，当进程创建新的文件时，(使用open(const char *pathname, int flags, mode_t mode))，文件的权限将是mode&0777*/
    umask(0);

    /*创建新的会话，设置本进程为进程组首领*/
    pid_t sid = setsid();
    if (sid < 0) {
        return false;
    }

    /*关闭标准输入、输出、错误输出*/
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /*关闭其他打开的文件描述符*/
    /* 切换工作目录 */

    /*标准输出，输出，错误输出重定向*/
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    return true;
}
