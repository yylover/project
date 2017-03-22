#ifndef __LOCK_H__
#define __LOCK_H__

typedef struct mutexLock {
    pthread_mutex_t mutex;
} mutexLock;

int pthreadMutexInit(mutexLock *ml);
int pthreadMutexLock(mutexLock *ml);
int pthreadMutexUnlock(mutexLock *ml);
int pthreadMutexDestroy(mutexLock *ml);

#endif
