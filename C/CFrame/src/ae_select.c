#include <sys/select.h>


typedef struct aeApiState {
    fd_set rfds, wfds;
    fd_set _rfds, _wfds;

} aeApiState;

static int aeApiCreate(aeEventLoop *eventloop) {
    aeApiState *state = malloc(sizeof(*state));

    if (!state) return -1;
    FD_ZERO(&state->rfds);
    FD_ZERO(&state->wfds);
    eventloop->apidata = state;
}

//仅判断是否超出
static int aeApiResize(aeEventLoop *eventloop, int setSize) {
    if (setSize >= FD_SETSIZE) return -1;
    return 0;
}

static int aeApiFree(aeEventLoop *eventloop) {
    free(eventloop->apidata);
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
    return 0;
}

static int aeApiPoll(aeEventLoop *eventloop, struct timeval *tvp) {
    aeApiState *state = (aeApiState *)eventloop->apidata;
    int retval, j, numevents = 0;

    memcpy(&state->_rfds, &state->rfds, sizeof(fd_set));
    memcpy(&state->_wfds, &state->wfds, sizeof(fd_set));
    retval = select(eventloop->maxfd+1, &state->_rfds, &state->wfds, NULL, tvp);
    if (retval > 0) {
        for (j = 0; j <= evnetloop->maxfd; j++) {
            int mask = 0;
            aeFileEvent *fd = &evnetloop->events[j];

            if (fd->mask = AE_NONE) continue;
            if (fd->mask & AE_READABLE && FD_ISSET(j, &state->_rfds))
                mask |= AE_READABLE;
            if (fd->mask & AE_WRITABLE && FD_ISSET(j, &state->_wfds))
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
