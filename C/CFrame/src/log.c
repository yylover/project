
#include "../include/log.h"

static char *logLevelName[] = {
    "FATAIL",
    "ERROR",
    "WARN",
    "NOTICE",
    "INFO",
    "DEBUG"
};

static log_t g_log; // 全局句柄

/** 私有函数原型 **/
static int logRotate(int fd, const char *path, int level);


/**
 * 根据ok的值，在屏幕输出红色或绿色，最长不超过80字符
 * @param ok      0 正常， 非0 错误
 * @param fmt     变长参数
 * @param VARARGS
 */
void bootNotify(int ok, const char *fmt, ...) {

}

/**
 * 初始化日志句柄
 * @param  dir      文件夹
 * @param  filename 文件名
 * @param  level    日志level
 * @param  size     大小限制
 * @param  logNum
 * @param  multi    是否不同等级的多个输出
 * @return
 */
int logInit(const char *dir, const char *filename, int level, int size, int logNum, int multi) {

}

/**
 * 写日志
 * @param  level   等级
 * @param  fmt     变长参数
 * @param  VARARGS [description]
 * @return         [description]
 */
int logWrite(int level, const char *fmt, ...) {

    // vasprint
}

/**
 * 关闭log句柄
 */
void logClose() {

}
