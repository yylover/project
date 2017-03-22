#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

/**

RTLD_LAZY：在dlopen返回前，对于动态库中的未定义的符号不执行解析（只对函数引用有效，对于变量引用总是立即解析）。
RTLD_NOW： 需要在dlopen返回前，解析出所有未定义符号，如果解析不出来，在dlopen会返回NULL，错误为：: undefined symbol: xxxx.......
 */


int main() {

    void *libmhandler = NULL;
    float (*cosf_method)(float) = NULL;
    int (*maxhandle) (int, int, int);
    int (*minHandle) (int, int);
    char *errorInfo;
    float result;

    libmhandler = dlopen("./libmax.so", RTLD_LAZY);
    // libmhandler = dlopen("./libmax.so", RTLD_LAZY);
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
