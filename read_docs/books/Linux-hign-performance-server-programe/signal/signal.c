#include <signal.h>


/**
 * linux下，进程给其他进程发送信号的函数。
 * pid > 0 目标进程
 *     = 0 本进程组内的同组进程
 *     = -1 发送给除了init进程外的所有进程。但发送者必须有对目标进程的权限。
 *     < -1 发送给组-pid的进程组中的所有成员
 * @param  pid 目标进程号
 * @param  sig 信号。一般> 0; 如果=0
 * @return     0|-1
 */
int kill(pid_t pid, int sig);

typedef void (*__sighandler_t)(int);
#define SIG_DFL ((__sighandler_t)0) //默认方式处理
#define SIG_ING ((__sighandler_t)1) //忽略信号

struct sigaction
{
#ifdef __USE_POSIX199309
    union
    {
        __sighandler_t sa_handler; //信号处理函数
        /* Used if SA_SIGINFO is set.     */
        void (*sa_sigaction) (int, siginfo_t *, void *);
    }
    __sigaction_handler;
# define sa_handler __sigaction_handler.sa_handler
# define sa_sigaction      __sigaction_handler.sa_sigaction
#else
    __sighandler_t sa_handler;
#endif

    __sigset_t sa_mask;//进程信号掩码，指示哪些信号不能发送给本进程
    int sa_flags;/* 指示应用程序收到信号的行为*/
    void (*sa_restorer) (void); //废弃
};



/**
 * 更加健壮的信号处理函数
 * @param  signum 信号number
 * @param  act    新的信号处理方式
 * @param  oldact 之前的捏好处理方式
 * @return        0|-1
 */
int sigaction(int signum,const struct sigaction *act,struct sigaction *oldact));

/**
 * 设置或查看进程的信号掩码
 * @param  how    SIG_BLOCK当前值与_set的并集；SIG_UNBLOCK 当前值与~_set并集;SIG_SETMASK 直接设置
 * @param  set    新的进程掩码
 * @param  oldset 原来的进程掩码
 * @return        0 |-1
 */
int  sigprocmask(int  how,  const  sigset_t *set, sigset_t *oldset)；
