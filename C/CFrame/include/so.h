#ifndef __SO_H__
#define __SO_H__

typedef struct symbolStruct {
    char *dymName; //动态库某个函数名称
    void **dymPtr; //动态库某个函数地址(二级指针)
    int no_error; // 1 不关心是否失败，0 失败后释放句柄
} symbolStruct;

int load_so(void **phandle, symbolStruct *sysm, const char *filename);
void unload_so(void **phandle);

#endif
