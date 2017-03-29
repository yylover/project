#ifndef __SIGNAL_H__
#define __SIGNAL_H__

typedef struct signalInfo {
    int signo;
    char *signame;
} signalInfo;

typedef struct threadPipeChannel {
    pthread_t tid;
    int readFd;
    int writeFd;
} threadPipeChannel;

threadPipeChannel * createThreadPipeChannel();

#endif
