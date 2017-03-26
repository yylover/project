#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

#include "../include/ae.h"

//包含当前系统支持的最大效率的ip复用方式,下面根据运行效率倒序排列
#ifdef HAVE_EVPORT
#include "ae_evport.c"
#else
    #ifdef HAVE_EPOLL
    #include "ae_epoll.c"
    #else
        #ifdef HAVE_KQUEUE
        #include "ae_kqueue.c"
        #else
            #include "ae_select.c"
        #endif
    #endif
#endif


aeEventLoop* aeCreateEventloop(int setSize) {
    aeEventLoop *eventloop;
    if ((eventloop = malloc(sizeof(*eventloop))) == NULL) {
        goto err;
    }
    if ((eventloop->events = malloc(sizeof(aeFileEvent) * setSize)) == NULL) {
        goto err;
    }
    if ((eventloop->fired = malloc(sizeof(aeFiredEvent) * setSize)) == NULL) {
        goto err;
    }

    eventloop->maxfd = -1;
    evnetloop->setSize = setSize;
    eventloop->lastTime = time(NULL); //当前时间戳
    eventloop->timeEventHead = NULL;
    eventloop->timeEventNextId = 0;//从0开始
    eventloop->stop = 0;
    eventloop->apidata = NULL;
    eventloop->beforeSleep = NULL;
    if (aeApiCreate(eventloop) == -1) {
        goto err;
    }

    int i;
    for (i = 0; i < setsize; i++) {
        eventloop->events[i].mask = AE_NODE;
    }

    return eventloop;
err:
    if (eventloop) {
        free(eventloop->events);
        free(eventloop->fired);
        free(eventloop);
    }
    return NULL;
}

void aeStop(aeEventLoop *eventloop) {
    eventloop.stop = 1;
}

int aeGetSetSize(aeEventLoop *eventloop) {
    return eventloop->setSize;
}

int aeResizeSetSize(aeEventLoop *eventloop, int setSize) {
    if (setSize == eventloop->setSize) return AE_OK;
    if (setSize <= eventloop->maxfd) return AE_ERR;
    if (aeApiResize(eventloop, setSize) == AE_ERR) {
        return AE_ERR;
    }

    eventloop->events = realloc(eventloop->events, sizeof(aeFileEvent) * SetSize);
    eventloop->fired = realloc(eventloop->fired, sizeof(aeTimeEvent) * SetSize);
    eventLoop->setsize = setsize;

    //确保新初始化的events 赋值为AE_NORE mask
    for (i = eventLoop->maxfd+1; i < setSize; i++) {
        eventloop->events[i].make = AE_NODE;
    }
    return AE_OK;
}

void aeDeleteEventLoop(aeEventLoop *eventloop) {
    aeApiFree(eventloop);
    free(eventloop->events);
    free(eventloop->fired);
    free(eventloop);
}

int aeCreateFileEvent(aeEventLoop *eventloop, int fd, int mask, aeFileProc *proc, void *clientData) {
    if (fd >= eventloop->setSize) {
        errno = ERANGE;
        return AE_ERR;
    }

    aeFileEvent *fe = &eventloop[fd];
    if (aeAddEvent(eventloop, fd, mask) == -1) {
        return AE_ERR;
    }

    fe->mask |= mask;
    if (mask & AE_READABLE) fd->rFileProc = proc;
    if (mask & AE_WRITABLE) fd->wFileProc = proc;
    fe->clientData = clientData;
    if (fd > eventloop->maxfd) { //更新maxfd
        eventloop->maxfd = fd;
    }
    return AE_OK;
}

void aeDeleteFileEvent(aeEventLoop *eventloop, int fd, int mask) {
    if (fd > eventloop->maxfd) {
        return ;
    }
    aeFileEvent *fd = &eventloop[fd];
    if (fd->mask == AE_NONE) return ;

    aeApiDelEvent(eventloop, fd, mask);
    fe->mask = fe->mask & (~mask);
    //更新maxfd
    if (fd == eventloop->maxfd && fe->mask == AE_NONE) {
        int j ;
        for (j = eventloop->maxfd-1; j>=0; j--) {
            if (eventloop[j].mask != AE_NONE) {
                break;
            }
        }
        eventLoop->maxfd = j;
    }
}

int aeGetFileEvents(aeEventLoop *eventloop, int fd) {
    if (fd > eventloop->setSize) {
        return 0;
    }
    return (eventloop->events[fd]).mask;
}

/**
 * 获取当前事件的秒数和毫秒数
 * @param seconds      [description]
 * @param milliseconds [description]
 */
static void aeGetTime(long *seconds, long *milliseconds) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    *seconds = tv.tv_sec;
    *milliseconds = tv.tv_usec /1000;
}

/**
 * 通过距离现在的毫秒数获取秒数和毫秒数
 * @param milliseconds 毫秒数
 * @param seconds      [description]
 * @param milliseconds [description]
 */
static void aeAddMillisecondsToNow(long long milliseconds, long *seconds, long *milliseconds) {
    long curSec, curMs, whenSec, whenMs;

    aeGetTime(&curSec, &curMs);
    whenSec = curSec + milliseconds / 1000;
    whenMs  = curMs  + milliseconds % 1000;
    if (whenMs >= 1000) {
        whenSec += whenMs /1000;
        whenMs  -= whenMs  %1000;
    }
    *seconds = whenSec;
    *milliseconds = whenMs;
}


/**
 * 创建时间事件
 * @param  eventloop     eventloop 指针
 * @param  id            id
 * @param  milliseconds  毫秒数
 * @param  proc          处理函数
 * @param  clientData    处理数据
 * @param  finalizerProc 最后的处理函数
 * @return
 */
int aeCreateTimeEvent(aeEventLoop *eventloop, long long id, long long milliseconds, aeTimeProc *proc, void *clientData, aeEventFinalizerProc *finalizerProc) {
    aeTimeEvent *te;
    if ((te == malloc(sizeof(*te))) == NULL) {
        return AE_ERR;
    }

    aeAddMillisecondsToNow(milliseconds, &te->when_sec, &te->when_ms);
    te->id = eventloop->timeEventNextId ++;
    te->timeProc = proc;
    te->finalizerProc = finalizerProc;
    te->clientData = clientData ;
    //采用头插法
    te->next = eventloop->timeEventHead;
    eventloop->timeEventHead = te;

    return AE_OK;
}

/**
 * 删除时间事件函数
 * @param eventloop eventloop 指针
 * @param id
 */
void aeDeleteTimeEvent(aeEventLoop *eventloop, long long id) {
    //遍历找到对应的时间事件
    aeTimeEvent *te, *prev = NULL;

    te = eventloop->timeEventHead;
    while (te) {
        if (te->id == id) {
            if (prev == NULL) {
                eventloop->timeEventHead = te->next;
            } else {
                prev->next = te->next;
            }

            //释放时间事件
            if (te->finalizerProc) {
                te->finalizerProc(eventloop, te->clientData);
            }
            free(te);
            return AE_OK;
        }
        prev = te;
        te = te->next;
    }
    return AE_ERR;
}

/**
 * 查找最近的一个定时器设置过期
 * @param  eventloop
 * @return
 */
static void aeTimeEvent *aeSearchNearestTimer(aeEventLoop *eventloop) {
    aeTimeEvent *te = NULL, *prev = NULL, *nearest = NULL;

    te = eventloop->timeEventHead;
    while (te) {
        // 判断记录最小的
        if (!nearest || te->when_sec < nearest->when_sec ||
            (te->when_sec == nearest->when_sec && te->when_ms < nearest->when_ms)) {
            nearest = te;
        }

        prev = te;
        te = te->next;
    }
    return nearest;
}

/**
 * 处理时间事件
 * @param  eventloop [description]
 * @return           [description]
 */
static int processTimeEvents(aeEventLoop *eventloop) {

}

/**
 * 处理文件和时间事件
 * @param  eventloop eventloop
 * @param  flags     AE_ALL_EVENTS|AE_FILE_EVENTS|AE_TIME_EVETNS
 *                   AE_ALL_EVENTS 处理所有事件
 *                   AE_FILE_EVENTS 处理文件事件
 *                   AE_TIME_EVETNS 处理时间事件
 *                   AE_DONT_WAIT 不处理，尽快返回
 * @return          处理的事件的个数
 */
int aeProcessEvents(aeEventLoop *eventloop, int flags) {
    int processed = 0, numevents = 0;

    if (!(flags & AE_TIME_EVETNS) && !(flags & AE_FILE_EVENTS)) {
        return AE_ERR;
    }

    //有文件事件或者  要处理时间事件但是没有设置非阻塞
    if (eventloop->maxfd > -1 || ((flags & AE_TIME_EVETNS) && !(flags & AE_DONT_WAIT))) {
        aeTimeEvent *shortest = NULL;
        struct timeval tv, *tvp;

        if (flags & AE_TIME_EVENTS && !(flags & AE_DONT_WAIT)) {
            shortest = aeSearchNearestTimer(eventloop);
        }
        if (shortest) {
            long now_sec, now_ms;
            aeGetTime(&now_sec, &now_ms);
            tvp = &tv;
            tvp->tv_sec = shortest->when_sec - now_sec;
            if (shortest->when_ms < now_ms) {
                tvp->tv_usec = ((shortest->when_ms+1000) - now_ms)*1000;
                tvp->tv_sec --;
            } else {
                tvp->tv_usec = (shortest->when_ms - now_ms) * 1000;
            }
            if (tvp->tv_sec < 0) tvp->tv_sec = 0;
            if (tvp->tv_usec < 0) tvp->tv_usec = 0;

        } else {
            if (flags & AE_DONT_WAIT) {//不能阻塞,return ASAP
                tv.tv_sec = tv.tv_usec = 0;
                tvp = &tv;
            } else { //可以阻塞
                tvp = NULL;
            }
        }

        numevents = aeApiPoll(eventloop, tvp);
        int j ;
        for (j = 0; j < numevents; j++) {
            aeFileEvent *fe = &eventloop->events[eventloop->fired[j].fd];
            int mask = eventloop->fired[j].mask;
            int fd = eventloop->fired[j].fd;
            int rfired = 0;

            if (fe->mask & mask & AE_READABLE) {
                rfired = 1;
                fe->rFileProc(eventloop, fd, fe->clientData, mask);
            }
            if (fe->mask & mask & AE_WRITABLE) {
                if (!rfired || fe->wFileProc != fe->rFileProc) {
                    fe->wFileProc(eventloop, fd, fe->clientData, mask);
                }
            }
            processed ++;
        }
    }

    if (flags & AE_TIME_EVETNS) {
        processed += processTimeEvents(eventloop);
    }
    return processed;
}

//等待milliseconds时间，直到fd变成可读、可写、异常
int aeWait(int fd, int mask, long long milliseconds) {

}


void aeMainLoop(aeEventLoop *eventloop) {
    eventloop->stop = 0;
    while (!eventloop->stop) {
        if (eventloop->beforeSleep) {
            eventloop->beforeSleep(eventloop);
        }
        aeProcessEvents(eventloop, AE_ALL_EVENTS);
    }
}

char *aeGetApiName(void) {
    return aeApiName();
}

void aeSetBeforeSleepProc(aeEventLoop *eventloop, aeBeforeSleepProc *proc) {
    eventloop->beforeSleep = proc;
}
