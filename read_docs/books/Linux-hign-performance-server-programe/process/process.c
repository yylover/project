#include <sys/types.h>
#include <unistd.h>

/**
 * 创建新的线程
 * @return 返回两次，父进程返回子进程的pid,子进程返回0,失败返回-1;
 */
pid_t fork(void);

#include <sys/types.h>
#include <sys/wait.h>

/**
 * 阻塞进程，直到某个子进程结束运行为止。
 * @param  stat_loc 获取子进程运行状态
 * @return          子进程pid
 */
pid_t wait(int *stat_loc);

/**
 * 只等待pid指定的子进程
 * @param  pid      -1,跟wait函数含义相同，>0 等待特定的子进程
 * @param  stat_loc 获取子进程运行状态。
 * @param  options  控制waitpid函数行为，常用WNOHANG,函数非阻塞。
 * @return          非阻塞调用时返回0，子进程还没有退出，>0,子进程pid,-1失败
 */
pid_t waitpid(pid_t pid, int *stat_loc, int options);

static void handle_child(int sig) {
    pid_t pid;
    int stat;
    while ((pid = waitpid(pid, &stat, WNOHANG)) > 0) {
        //对结束的子进程进行处理
    }
}
