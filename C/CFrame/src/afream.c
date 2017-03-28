#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "../include/afream.h"
#include "../include/options.h"
#include "../include/anet.h"
#include "../include/master.h"
#include "../include/log.h"


#define CONFIG_FILENAME_MAXLENGTH 128
#define PROGRAME_NAME "afream"
#define PROGRAME_VERSION "1.1"

int gStartMode;

//优化的通知程序启动，停止和重启
typedef enum startMode {
    PROGRAM_START,
    PROGRAM_STOP,
    PROGRAM_RESTART,
} startMode;


void *workerTask(void *data) {
    return NULL;
}

struct option longopts[] = {
    {"config",  required_argument, NULL, 'c'},
    {"version", no_argument, NULL, 'v'},
    {"info",    no_argument, NULL, 'i'},
    {"help",    no_argument, NULL, 'h'},
    {0, 0, 0, 0}
};

/**
 * 创建程序实例
 * @param  opts 配置选项
 * @return
 */
static instance_t* createInstance(options_t *opts) {
    instance_t *instance = (instance_t*) malloc(sizeof(*instance));
    if (NULL == instance) {
        LOG_INFO("instance null");
        return NULL;
    }
    memset(instance, 0, sizeof(*instance));

    instance->pool = threadPoolCreate(opts->workerNum, opts->stackSize, workerTask);
    if (!instance->pool) {
        LOG_INFO("instance null");
        free(instance);
        return NULL;
    }

    instance->opts =  opts;
    return instance;
}

/**
 * 释放当前程序实例
 * @param instance
 */
static void destroyInstance(instance_t *instance) {
    threadPollDestroy(instance->pool);
    free(instance->opts);
    free(instance);
}

static void printInfo() {
    printf("[%s]: An async network server framework.\n"
          "Version: %s\n"
          "Copyright(c): hq, hq_cml@163.com\n"
          "Compiled at: %s %s\n", PROGRAME_NAME, PROGRAME_VERSION,
          __DATE__, __TIME__);
}

static void printVersion() {
    printf("version: %s\n", PROGRAME_VERSION);
}

static void printUsage(int status) {
    if (status != EXIT_SUCCESS) {
        fprintf(stderr, "Try '%s --help' for more information.\n", PROGRAME_NAME);
    } else {
        printf("Usage:./%6.6s [--config=<conf_file> | -c] [start|stop|restart]\n"
               "%6.6s         [--version | -v]\n"
               "%6.6s         [--help | -h]\n", PROGRAME_NAME, " ", " ");
    }
}


/**
 * 解析命令行参数
 * @param argc [description]
 * @param argv [description]
 */
static void getCommandArgs(int argc, char **argv, char *configFile) {
    int c ;
    while((c = getopt_long(argc, argv, "c:vih", longopts, NULL)) != -1) {
        switch(c) {
            case 'c':
                if (optarg && strlen(optarg) < CONFIG_FILENAME_MAXLENGTH) {
                    strcpy(configFile, optarg);
                } else {
                    printUsage(EXIT_FAILURE);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'v':
                printVersion();
                exit(EXIT_SUCCESS);
                break;
            case 'i':
                printInfo();
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                printUsage(EXIT_SUCCESS);
                exit(EXIT_SUCCESS);
            default:
                printUsage(EXIT_FAILURE);
                exit(EXIT_FAILURE);
        }
    }
    printf("optind :%d %d %s \n",argc, optind, argv[optind]);

    if (optind + 1 == argc) {
        if (!strcasecmp(argv[optind], "stop")) { //相等
            gStartMode = PROGRAM_STOP;
        } else if (!strcasecmp(argv[optind], "restart")) { //相等
            gStartMode = PROGRAM_RESTART;
        } else if (!strcasecmp(argv[optind], "start")) { //相等
            gStartMode = PROGRAM_START;
        } else {
            printUsage(EXIT_FAILURE);
            exit(EXIT_FAILURE);
        }

    } else if (optind == argc) {
        gStartMode = PROGRAM_START;
    } else { //异常 ?
        printUsage(EXIT_FAILURE);
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char **argv) {
    char configFile[CONFIG_FILENAME_MAXLENGTH];
    memset(configFile, 0, CONFIG_FILENAME_MAXLENGTH);
    getCommandArgs(argc, argv, configFile);
    if (configFile[0] == '\0') {
        strcpy(configFile, "afream.conf");
    }

    options_t *opts = getOptions(configFile);
    if (opts == NULL) {
        printf("options is null %s\n", configFile);
        exit(EXIT_FAILURE);
    }
    instance_t *instance = createInstance(opts);
    if (instance == NULL) {
        LOG_INFO("instance is null");
        return -1;
    }

    LOG_INFO("hello");
    // instance->pool = threadPoolCreate();
    // 主线程 创建tcp server 并且等待accept
    // accept 之后添加一个新的socket fd 到监控列表中
    //
    char err[128];
    int sock = anetTcpServer(err, 8000, "127.0.0.1", 10);
    masterCycle(sock, 1000, 10);

    destroyInstance(instance);
    destroyOptions(opts);
    return 0;
}
