#ifndef __SIGNAL_H__
#define __SIGNAL_H__

typedef struct signalInfo {
    int signo;
    char *signame;
} signalInfo;

typedef struct threadPipeChannel {
    int readFd;
    int writeFd;
} threadPipeChannel;

threadPipeChannel * createThreadPipeChannel();
void destroyThreadPipeChannel(threadPipeChannel *chan);

//私有信号处理
int handlePrivateSignals();
//公共信号，出发时，将信号写入到chan中
int handlePublicSignals(threadPipeChannel *chan);

#endif
