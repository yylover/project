#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/adlist.h"
#include "../include/options.h"

options_t *getDefaultOptions() {
    options_t *opts = (options_t *) malloc(sizeof(*opts));
    if (NULL == opts) {
        return NULL;
    }
    memset(opts, 0, sizeof(*opts));
    opts->workerNum = 2;
    opts->soName = "demo.so";

    opts->serverIp = "127.0.0.1";
    opts->serverPort = 8000;
    opts->maxClients = 1000;

    opts->stackSize = 10*1024*1024; //10M

    return opts;
}

int updateOptionsFromConfig(options_t* opts, char *configFile) {

    return 0;
}

void destroyOptions(options_t *opts) {
    free(opts);
}

options_t *getOptions(char *configFile) {
    if (!configFile) {
        return NULL;
    }

    if (access(configFile, R_OK) != 0) {
        return NULL;
    }
    options_t *opts = getDefaultOptions();


    //读取配置文件
    if (updateOptionsFromConfig(opts, configFile) != 0) {
        return NULL;
    }

    return opts;
}
