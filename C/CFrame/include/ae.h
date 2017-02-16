

#ifdef __AE_H__
#define __AE_H__

#define AE_OK 0
#define AE_ERR -1

#define AE_NODE 0
#define AE_READABLE 1
#define AE_WRITABLE 2

#define AE_FILE_EVENTS 1
#define AE_TIME_EVETNS 2
#define AE_ALL_EVENTS (AE_FILE_EVENTS|AE_TIME_EVETNS)
#define AE_DONT_WAIt 4

#define AE_NOMORE 0

//宏定义，仅仅为了去掉警告？
// #define AE_NOTUSED(V) ((void) V)

struct aeEventLoop;
typedef void aeFileProc(struct aeEventLoop *eventloop, int fd, void *clientData, int mask); //文件时间处理逻辑
typedef int  aeTimeProc(struct aeEventLoop *eventloop, long long id, void *clientData); //定时事件处理函数
typedef void aeEventFinalizerProc(struct aeEventLoop *eventloop, void *clientData);
typedef void aeBeforeSleepProc(struct aeEventLoop *eventloop);

typedef struct aeFileEvent {
    //fd 是如何传递的
    int maske;
    aeFileProc *rFileProc;  //读时间处理函数
    aeFileProc *wFileProc;  //写事件处理函数
    void *clientData;// TODO 有bug,可能会造成数据覆盖?
} aeFileEvent;

typedef struct aeTimeEvent {
    long long id;  //时间事件的唯一标识
    long when_sec; //定时秒数
    long when_ms;  //定时毫秒数
    aeTimeProc *timeProc; //时间
    aeEventFinalizerProc *finalizerProc;
    void *clientData; //
    struct aeTimeEvent *next; //数据结构是链表?
} aeTimeEvent;

//到期事件
typedef struct aeFiredEvent {
    int fd;
    int mask;
} aeFiredEvent;

typedef struct aeEventLoop {
    int maxfd; //最大的文件描述符
    int setsize; //文件描述符追踪的个数?
    long long timeEventNextId; //
    time_t lastTime;
    aeFileEvent *event;
    aeFiredEvent *fired;
    aeTimeEvent *timeEventHead;
    int stop;
    void *apidata; //用来poll
    aeBeforeSleepProc *beforeSleep;
} aeEventLoop;

//函数原型
aeEventLoop* aeCreateEventloop(int setSize);
void aeDeleteEventLoop(aeEventLoop *eventloop);
void aeStop(aeEventLoop *eventloop);

int aeCreateFileEvent(aeEventLoop *eventloop, int fd, int mask, aeFileProc *proc, void *clientData);
void aeDeleteFileEvent(aeEventLoop *eventloop, int fd, int mask); //删除
int aeGetFileEvents(aeEventLoop *eventloop, int fd);

int aeCreateTimeEvent(aeEventLoop *eventloop, long long id, long long milliseconds, aeTimeProc *proc, void *clientData, aeEventFinalizerProc *finalizerProc);
void aeDeleteTimeEvent(aeEventLoop *eventloop, long long id);

int aeProcessEvents(aeEventLoop *eventloop, int flags);
int aeWait(int fd, int mask, long long milliseconds);
void aeMain(aeEventLoop *eventloop);
char *aeGetApiName(void);
void aeSetBeforeSleepProc(aeEventLoop *eventloop, aeBeforeSleepProc *proc);
int aeGetSetSize(aeEventLoop *eventloop);
int aeResizeSetSize(aeEventLoop *eventloop, int setsize);

#endif
