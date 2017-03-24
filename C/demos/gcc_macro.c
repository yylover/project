#include <stdio.h>


int main () {
#ifdef DEBUG
    printf("defined debug\n");
#else
    printf("debug not defined\n");
#endif
    printf("%d\n", DEBUG);

#ifdef HELLO
    printf("defined debug\n");
#else
    printf("debug not defined\n");
#endif
    printf("%d\n", DEBUG);
    return 0;
}
