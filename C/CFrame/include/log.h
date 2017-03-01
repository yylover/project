#ifndef __LOG_H__
#define __LOG_H__


#define LOG_LEVEL_FATAL   0
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_NOTICE  2
#define LOG_LEVEL_INFO    4
#define LOG_LEVEL_DEBUG   5
#define LOG_LEVEL_ALL     LOG_LEVEL_DEBUG

#define LOG_FILE_SIZE (1<<30) /*2G*/
#define LOG_MULTIMODE_NO  0
#define LOG_MULTIMODE_YES 1
#define LOG_FILE_NUM      10

#define SCREEN_COLS        80
#define CONTENT_COLS       65

#define LOG_BUFFER_SIZE   4096
#define LOG_MAX_BUFFER     100
#define LOG_PATH_MAX      1024

typedef struct s_log_t {
    int fd;
    char path[LOG_PATH_MAX];
} s_log_t;

typedef struct log_t {
    int logInited; //是否已经初始化
    int logLevel;  // 等级
    int logSize;   //  大小
    int logNum;    // 最多允许的日志个数
    int logMulti;  //是否允许不同等级的日志写入不同的文件
    //lock
    s_log_t logFiles[LOG_LEVEL_DEBUG+1]; //不同等级的文件句柄
} log_t;

#define BOOT_SUCCESS(fmt, args...) do {\
    threadUsleep(40000);\
    bootNotify(0, fmt, ##args);\
} while(0)

#define BOOT_FAILED(fmt, args...) do {\
    bootNotify(-1, fmt, ##args);\
    exit(1);\
} while(0)

#define LOG_DETAIL(level, fmt, args...) \
    logWrite(level, "[%s:%d:%s] " fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#define LOG_FATAL(fmt, args...) LOG_DETAIL(LOG_LEVEL_FATAL, fmt, ##args)
#define LOG_ERROR(fmt, args...) LOG_DETAIL(LOG_LEVEL_ERROR, fmt, ##args)
#define LOG_WARNING(fmt, args...) LOG_DETAIL(LOG_LEVEL_WARNING, fmt, ##args)
#define LOG_NOTICE(fmt, args...) LOG_DETAIL(LOG_LEVEL_NOTICE, fmt, ##args)
#define LOG_INFO(fmt, args...) LOG_DETAIL(LOG_LEVEL_INFO, fmt, ##args)
#define LOG_DEBUG(fmt, args...) LOG_DETAIL(LOG_LEVEL_DEBUG, fmt, ##args)

void bootNotify(int ok, const char *fmt, ...);
int logInit(const char *dir, const char *filename, int level, int size, int logNum, int multi);
int logWrite(int level, const char *fmt, ...);
void logClose();


#endif
