
1. 后台进程方式运行;
2. 有一套日志系统，一般在/var/log下有自己的日志目录。
3. 运行账号，非root身份.
4. 通常是可配置的，有很多命令行选项，大多数配置文件放置在/etc/下
5. 通常考虑系统资源和限制。

### 日志
    可以使用syslog与rsyslogd守护进程通信，用来输出日志。

### 用户信息
```
#include<sys/types.h>
#include<unistd.h>
uid_t getuid(void); // 获取用户的uid
uid_t geteuid(void); // 用去有效用户id
gid_t getgid();     //获取真实组ID
git_t getegid();   // 获取有效组ID
int setuid(uid_t uid);
int seteuid(uid_t uid);
int setgid(git_t git);
int setegid(git_t gid);
```
1. EUID:存在是方便资源访问，使得运行程序的用户拥有该程序的有效用户的权限。
2. Egid:给运行目标程序的组用户提供有效组的权限。

```
sudo chown root:root ./a.out

```

### 切换用户
root 用户启动以另一个用户执行的例子
```
static bool switch_to_user (uid_t user_id, gid_t gp_id) {
    //确保用户不是root
    if ((user_id == 0) && (gp_id == 0)) {
        return false;
    }

    //确保当前用户是合法用户:root 或者目标用户
    gid_t gid = getgid();
    uid_t uid = getuid();
    if ((gid != 0 || uid != 0) && (gid != gp_id || uid != user_id)) {
        return false;
    }

    //如果不是root,则已经是目标用户
    if (uid != 0) {
        return true;
    }

    //切换到目标用户
    if ((setgid(gp_id) < 0) || (getuid(user_id) < 0)) {
        return false;
    }

    return true;
}
```

### 进程关系

#### 进程组
进程有PID和PGID信息，每个进程组有一个pgid,
```
pid_t getpgid(pid_t pid);
/**
 * 用户进程的进程组id
 * @param  pid  0设置当前进程，如果pid=pgid,则pid为进程组首领
 * @param  pgid 进程组id
 * @return
 */
int setpgid(pid_t pid, pid_t pgid);
```
#### 会话

1. 一些有关联的进程组将形成一个会话session, 该函数不能由组的首领进程调用。
2. 非首领进程调用时:
    1) 调用进程成为会话的新首领，该进程是新会话的唯一成员。
    2）新建一个进程组，其PGID就是调用进程的PID,调用进程称为该组首领。
    3）调用进程将甩开终端。
```
pid_t setsid(void);
PID  PPID  PGID   SID COMMAND
4445 32626  4445 32626 ps
4446 32626  4445 32626 less
32626 32625 32626 32626 bash
```
http://7ktumn.com1.z0.glb.clouddn.com/WechatIMG2.jpeg

#### 系统资源限制
```
#include <sys/resourceh>
struct rlimit {
    rlimit rlim_cur; //指定软限制
    rlimit rlim_max; // 指定硬限制
};
int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);
```
资源限制类型 | 含义
---|---
RLIMIT_AS | 虚拟内存总量限制
RLIMIT_CORE | 进程核心转储文件core dump 大小
RLIMIT_CPU | cpu 时间限制
RLIMIT_DATA | 进程数据段
RLIMIT_NOFILE | 文件描述符限制
RLIMIT_NPROC | 用户创建的进程数量限制
RLIMIT_SIGPENDING | 用户能够挂起的信号数量限制
RLIMIT_STACK | 进程栈内存限制

### 改变工作目录和根目录

```
#include <unistd.h>
char *getcwd(char *buf, size_t size); //获取当前的工作目录
int chdir(const char *path);          //改变进程工作目录
int chroot(const char *path); //改变进程根目录
```


### 后台化

```
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
```
