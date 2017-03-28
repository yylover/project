#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
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
    return 0;
}

/**
 * 写日志
 * @param  level   等级
 * @param  fmt     变长参数
 * @param  VARARGS [description]
 * @return         [description]
 */
int logWrite(int level, const char *fmt, ...) {
    va_list ap;
    va_list ap_cpy;
    int buf_len = 16;
    char *buf = NULL;

    va_start(ap, fmt);
    while (1) {
        if (!(buf = malloc(buf_len))) {
            return -1;
        }

        memset(buf, 0, buf_len);
        buf[buf_len-2] = '\0';
        va_copy(ap_cpy, ap);
        vsnprintf(buf, buf_len, fmt, ap_cpy);
        if (buf[buf_len-2] != '\0') {
            free(buf);
            buf_len *=2; //倍数
            continue;
        }
        break;
    }
    va_end(ap);

    printf("%s\n", buf);
    free(buf);
    return 0;
    // vasprint
}

/**
 * 关闭log句柄
 */
void logClose() {

}
