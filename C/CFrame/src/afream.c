#include "../include/afream.h"



int main() {

    instance_t *instance = (instance_t*) malloc(sizeof(*instance));
    if (instance == NULL) {
        //ERROR
        return -1;
    }
    memset(instance, 0, sizeof(*instance));

    // instance->pool = threadPoolCreate();

    // 主线程 创建tcp server 并且等待accept

    // accept 之后添加一个新的socket fd 到监控列表中

    //
    //
    //


    return 0;
}
