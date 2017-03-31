#ifndef __MASTER_H__
#define __MASTER_H__

#include <time.h>
#include "string.h"
#include "vector.h"
#include "ae.h"
#include "signal.h"

//主线程主要开始server并监听连接套接字

typedef enum masterStatus {
    RUNNING,
    STOPING,
    STOPED
} masterStatus;

typedef enum ClientStatus {
    COMMING,
    DISPATCHING,
    WAITING,
    RECEIVING,
    PROCESSING,
    ACCEPTED,
    CONNECTED,
    CLOSING
} ClientStatus;

typedef struct masterThread {
    int     listenfd;       //当前的监听描述符
    int     clientLimit;    //client连接数限制
    int     pollInterval;   //cron频率
    masterStatus status;    //主线程状态
    mutexLock *lock;        //互斥锁

    int    curConn;         //上一次新增client在clientVec中的位置
    int    curThread;       //
    int    totalClients;    //连接总数
    vector *clients;        // 所有的连接
    aeEventLoop *eventloop; //事件循环
} masterThread;

typedef struct Client {
    int fd;              // fd 套接字
    int closeConn;       // 是否发送响应后就关闭连接
    ClientStatus status; // 连接状态
    char *remoteIp;      //
    int remotePort;      //
    int recvProtoLen;    // 客户端协商协议头长度
    string *sendbuf;     // 发送缓冲区
    string *recvbuf;     // 接收缓冲区
    time_t accessTime;   // 接收连接的时间

    int idx;             //在clientVec中的位置
    int workerId;        //负责该连接的workerId
} Client;


void masterCycle(int listenfd, int clientLimit, int pollInterval, threadPipeChannel *chan); // 主线程循环
void closeClientByIndx(int clientIdx, char *info);
int masterDestroy(masterThread *master);

#endif
