#include <sys/select.h>


/*
select 方式
最大支持描述符个数1024



*/


typedef struct aeApiState {
    fd_set rfds, wfds;
    //rfds 和wfds 的备份，这样select()之后不用重新重置rfds,wfds的状态
    fd_set _rfds, _wfds;
} aeApiState;

static int aeApiCreate(aeEventLoop *eventloop) {
    aeApiState *state = malloc(sizeof(*state));

    if (!state) return -1;
    FD_ZERO(&state->rfds);
    FD_ZERO(&state->wfds);
    eventloop->apidata = state;
    return 0;
}

//仅判断是否超出
static int aeApiResize(aeEventLoop *eventloop, int setSize) {
    if (setSize >= FD_SETSIZE) return -1;
    return 0;
}

static int aeApiFree(aeEventLoop *eventloop) {
    free(eventloop->apidata);
    return 0;
}

static int aeApiAddEvent(aeEventLoop *eventloop, int fd, int mask) {
    aeApiState *state = (aeApiState *)eventloop->apidata;

    if (mask & AE_READABLE) FD_SET(fd, &state->rfds);
    if (mask & AE_WRITABLE) FD_SET(fd, &state->wfds);
    return 0;
}

static void aeApiDelEvent(aeEventLoop *eventloop, int fd, int delmask) {
    aeApiState *state = (aeApiState *)eventloop->apidata;

    if (delmask & AE_READABLE) FD_CLR(fd, &state->rfds);
    if (delmask & AE_WRITABLE) FD_CLR(fd, &state->wfds);
}


static int aeApiPoll(aeEventLoop *eventloop, struct timeval *tvp) {
    aeApiState *state = (aeApiState *)eventloop->apidata;
    memcpy(&state->_rfds, &state->rfds, sizeof(fd_set));
    memcpy(&state->_wfds, &state->wfds, sizeof(fd_set));

    int retval, j, numevents = 0;
    retval = select(eventloop->maxfd+1, &state->_rfds, &state->wfds, NULL, tvp);
    if (retval > 0) {
        for (j = 0; j <= eventloop->maxfd; j++) {
            aeFileEvent *fe = &eventloop->events[j];

            int mask = 0;
            if (fe->mask == AE_NONE) continue; //没有设置
            if (fe->mask & AE_READABLE && FD_ISSET(j, &state->_rfds))
                mask |= AE_READABLE;
            if (fe->mask & AE_WRITABLE && FD_ISSET(j, &state->_wfds))
                mask |= AE_WRITABLE;
            eventloop->fired[numevents].fd = j;
            eventloop->fired[numevents].mask = mask;
            numevents++;
        }
    }
    return numevents;
}

static char *aeApiName(void) {
    return "select";
}
