#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
#ifdef HAVE_EVPORT
    printf("evport");
#elif HAVE_EPOLL
    printf("epoll");
#elif HAVE_KQUEUE
    printf("HAVE_KQUEUE");
#else
    printf("select");
#endif
    char *p = NULL;
    size_t t = time(NULL);

    printf("%zu", t);
    printf("NULL == 0: %d", NULL == 0);
    free(p);
    return 0;
}
