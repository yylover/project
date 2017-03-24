#include "../include/so.h"
#include <fcn.h>

/**
 * 1. dlopen() 之后，最后才能dlclose()，否则dlsym()打开的函数是不可用的
 * 2. RTLD_LAZY| RTLD_NOW 区别
 *
 * 3. 动态Loading方式加载动态链接库，如果不是通过dlsym()打开，直接回传函数指针是不能执行的。 ？
 *
 *
 */


int load_so(void **phandle, symbolStruct *sysm, const char *filename) {
    *phandle = dlopen("./libmax.so", RTLD_LAZY); //RTLD_NOW
    if (*phandle == NULL) {
        fprintf(stderr, "Open error:%s\n", dlerror());
        return -1;
    }

    maxhandle = dlsym(libmhandler, "max");
    if (maxhandle == NULL) {
        printf("dlsym error: %s\n", dlerror());
        return 0;
    }

    int i = 0;
    while (sym[i].sym_name) {
        if (sym[i].no_error) { //可以允许失败
            //TODO
            sym[i].sym_ptr = dlsym(*phandler, sym[i].sym_name);
            dlerror();
        } else {
            sym[i].sym_ptr = dlsym(*phandler, sym[i].sym_name);
            if (dlerror() != NULL) {
                unload_so(phandle);
                return -1;
            }
        }
        i++;
    }

    return 0;
}

void unload_so(void **phandle) {
    if (*phandle != NULL) {
        dlclose(*phandle);
        *phandle = NULL;
    }
}
