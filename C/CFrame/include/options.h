#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "adlist.h"

/**
 * 全局配置
 * 默认-->配置文件-->命令行
 */
typedef struct options {
    int workerNum; //工作线程数
    char *soName;  //动态连接库名称

    char *serverIp;  //服务器IP
    int serverPort; //服务器端口号
    int  maxClients;  //最大连接数

    //线程
    int stackSize;

    list *linklist;

} options_t;


options_t *getOptions(char *configFile);
void destroyOptions(options_t *opts);

#endif
