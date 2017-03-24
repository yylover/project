#ifndef __AFREAM_H__
#define __AFREAM_H__
#include "athread.h"

/**
 * 全局配置
 * 默认-->配置文件-->命令行
 */
typedef struct options {
    int workerNum; //工作线程数
    char *soName;  //动态连接库名称

    char *serverIp;  //服务器IP
    char *serverPort; //服务器端口号
    int  maxClients;  //最大连接数

    adlist *linklist;

} options_t;

typedef struct instance_t  {
    threadPool *pool;
    options_t  *opts; //全局配置文件句柄

} instance_t;


#endif
