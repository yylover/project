#include "../include/so.h"
#include <fcn.h>

int load_so(void **phandle, symbolStruct *sysm, const char *filename) {
    *phandle = dlopen("./libmax.so", RTLD_LAZY);
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
