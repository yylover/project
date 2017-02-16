
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <stdib.h>
#include <sys/time.h>
#include <sys/types.h>

#include "../src/ae.h"

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
    int i;
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
    eventloop->lastTime = time(NULL); //?
    eventloop->timeEventHead = NULL;
    eventloop->timeEventNextId = 0;//从0开始
    eventloop->stop = 0;
    eventloop->apidata = NULL;
    eventloop->beforeSleep = NULL;
    if (aeApiCreate(eventloop) == -1) {
        goto err;
    }

    for (i = 0; i < setsize; i++) {
        eventloop->events[i].mask = AE_NODE;
    }

    return eventloop;
err:
    if (eventloop) {
        if (eventloop->events) free(eventloop->events);
        if (evnetloop->fired) free(eventloop->fired);
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
    if (aeApiResize(eventloop, setSize) == -1) {
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
    return eventloop->events[fd].mask;
}


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

//等待milliseconds时间，直到fd变成可读、可写、异常
int aeWait(int fd, int mask, long long milliseconds) {

}

void aeMain(aeEventLoop *eventloop) {
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
