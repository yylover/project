#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {

    void *libmhandler = NULL;
    float (*cosf_method)(float) = NULL;
    int (*maxhandle) (int, int, int);
    int (*minHandle) (int, int);
    char *errorInfo;
    float result;

    libmhandler = dlopen("./libmax.so", RTLD_LAZY);
    if (libmhandler == NULL) {
        printf("Open error:%s\n", dlerror());
        return 0;
    }

    maxhandle = dlsym(libmhandler, "max");
    if (maxhandle == NULL) {
        printf("dlsym error: %s\n", dlerror());
        return 0;
    }

    /*
    minHandle = dlsym(libmhandler, "min");
    if (minHandle == NULL) {
        printf("dlsym error:%s\n", dlerror());
        return 0;
    }*/

    int res = maxhandle(4, 7, 2);
    printf("result : %d\n", res);

    dlclose(libmhandler);

    return 0;
}
