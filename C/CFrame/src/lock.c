#include "../lock.h"
#include <pthread.h>

int pthreadMutexInit(mutexLock *ml) {
    return pthread_mutex_init(ml->mutex, NULL, NULL);
}
int pthreadMutexLock(mutexLock *ml) {
    return pthread_mutex_lock(&ml->mutex);
}
int pthreadMutexUnlock(mutexLock *ml) {
    return pthread_mutex_unlock(&ml->mutex);
}
int pthreadMutexDestroy(mutexLock *ml) {
    return pthread_mutex_destroy(ml->mutex)
}
