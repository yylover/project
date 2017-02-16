#include <sys/epoll.h>


typedef struct aeApiState {
    int epfd;
    struct epoll_event *events;
} aeApiState;

static int aeApiCreate(aeEventLoop *eventloop) {
    aeApiState *state;
    if ((state = malloc(sizeof(*state))) == -1) {
        return -1;
    }

    state->events = malloc(sizeof(epoll_event) * eventloop->setSize);
    if (state->events == -1) {
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

    struct epoll_event ee;
    int op = eventloop->events[fd].mask == AE_NONE ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;

    ee.events = 0;
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

}

static int aeApiPoll(aeEventLoop *eventloop, struct timeval *tvp) {

}

static char *aeApiName(void) {
    return "epoll";
}
