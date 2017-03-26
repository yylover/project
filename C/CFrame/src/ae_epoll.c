#include <sys/epoll.h>


typedef struct aeApiState {
    int epfd;
    struct epoll_event *events;
} aeApiState;

static int aeApiCreate(aeEventLoop *eventloop) {
    aeApiState *state;
    if ((state = malloc(sizeof(*state))) == NULL) {
        return -1;
    }

    state->events = malloc(sizeof(epoll_event) * eventloop->setSize);
    if (state->events == NULL) {
        free(state);
        return -1;
    }

    state->epfd = epoll_create(1024); //内核提示
    if (state->epfd == -1) {
        free(state->events);
        free(state);
        return -1;
    }
    eventloop->apidata = state;
    return 0;
    // epoll_create(1024);
}


static int aeApiResize(aeEventLoop *eventloop, int setSize) {
    aeApiState *state = (aeApiState *)eventloop->apidata;

    state->events = realloc(state->events, sizeof(epoll_event) *setSize);
    return 0;
}

static void aeApiFree(aeEventLoop *eventloop) {
    aeApiState *state = (aeApiState *)eventloop->apidata;

    free(state->events);
    free(state);
}

static int aeApiAddEvent(aeEventLoop *eventloop, int fd, int mask) {
    aeApiState *state = (aeApiState *)eventloop->apidata;
    int op = eventloop->events[fd].mask == AE_NONE ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;

    struct epoll_event ee;
    ee.events = 0; //清空
    mask |= eventloop->events[fd].mask;
    if (mask & AE_READABLE) ee.events |= EPOLLIN;
    if (mask & AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.u64 = 0;
    ee.data.fd = fd;
    if (epoll_ctl(state->epfd, op, fd, &ee) == -1)
        return -1;
    return 0;
}


static void aeApiDelEvent(aeEventLoop *eventloop, int fd, int delmask) {
    aeApiState *state = (aeApiState *)eventloop->apidata;

    int mask = eventloop->events[fd].mask & (~delmask);

    ee.events = 0;
    if (mask && AE_READABLE) ee.events |= EPOLLIN;
    if (mask && AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.u64 = 0;
    ee.data.fd = fd;
    if (mask != AE_NONE) {
        epoll_ctl(state->epfd, EPOLL_CTL_MOD, fd, &ee);
    } else {
        //EPOLL_CTL_DEL 内核<2.6.9需要一个非空的event pointer 指针
        epoll_ctl(state->epfd, EPOLL_CTL_DEL, fd, &ee);
    }
}

static int aeApiPoll(aeEventLoop *eventloop, struct timeval *tvp) {
    aeApiState *state = (aeApiState *)eventloop->apidata;
    int retval, numevents = 0;

    int timeout = tvp ? (tvp->tv_sec * 1000 + tvp->tv_usec/1000) : -1;
    retval = epoll_wait(eventloop->epfd, state->events, eventloop->setSize, tvp);
    if (ret != -1) {
        int j ;
        numevents = retval;
        for (j = 0; j < numevents; j++) {
            int mask = 0;
            struct epoll_event *ee = state->events+j;
            if (ee->events & EPOLLIN) mask |= AE_READABLE;
            if (ee->events & EPOLLOUT) mask |= AE_WRITABLE;
            if (ee->events & EPOLLERR) mask |= AE_WRITABLE;
            if (ee->events & EPOLLHUB) mask |= AE_WRITABLE;

            eventloop->fired[j].fd = e->data.fd;
            eventloop->fired[j].mask = mask;
        }
    }

    return numevents;
}

static char *aeApiName(void) {
    return "epoll";
}
