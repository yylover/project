#include "../include/signal.h"

threadPipeChannel * createThreadPipeChannel() {
    threadPipeChannel* chan = (threadPipeChannel*) malloc(sizeof(*chan));
    if (chan == NULL) {
        return NULL;
    }

    int fds[2];
    if (pipe(fds) != 0) {
        free(chan);
        return NULL;
    }

    chan->readFd = fds[0];
    chan->writeFd = fds[1];

    //设置非阻塞 TODO
    if (0 != anetNonBlock(fds[0]) || 0 != anetNonBlock(fds[1])) {
        free(chan);
        return NULL;
    }

    return chan;

}
