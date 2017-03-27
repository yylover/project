#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include "../include/string.h"

static const unsigned char g_default_ifs[256] = {[9]=1, [10]=1, [13]=1, [32]=1};

static string* stringNewLen(const void *init, size_t len);

static inline size_t stringLen(const string *pstr) {
    if (pstr) {
        return pstr->len;
    } else {
        return -1;
    }
}

static inline size_t stringAvail(const string *pstr) {
    if (pstr) {
        return pstr->size - pstr->len -1;
    } else {
        return -1;
    }
}

/**
 * 获取string 一共分配的空间
 * @param  pstr 指针
 * @return
 */
static inline size_t stringAllocSize(const string *pstr) {
    return sizeof(string) + pstr->size;
}

/**
 * 创建新的字符串
 * @param  init 初始化字符串
 * @param  len  初始化长度
 * @return
 */
static string* stringNewLen(const void *init, size_t len) {
    string *pstr = calloc(1, sizeof(*pstr)+len+1);
    if (pstr == NULL) {
        return NULL;
    }

    pstr->len = len;
    pstr->size = len+1;

    if (len && init) {
        memcpy(pstr->buf, init, len);
    }

    pstr->buf[len] = '\0';
    return pstr;
}

string* stringNew(const void *init) {
    size_t len = (init == NULL) ? 0 : strlen(init);
    return stringNewLen(init, len);
}

string* stringNewEmpty(void) {
    return stringNewLen("", 0);
}

string* stringDup(string *init) {
    if (init && init->len > 0) {
        return stringNew((const void *) init->buf);
    } else {
        return NULL;
    }
}

/**
 * 释放字符串
 * @param  str
 * @return
 */
void stringFree(string *pstr) {
    if (pstr) {
        pstr->buf[0] = '\0';
        pstr->len = 0;
        pstr->size = 0;
        free(pstr);
    }
}

/**
 * 清空字符串
 * @param  str
 * @return
 */
void    stringClear(string *pstr) {
    if (pstr) {
        pstr->len = 0;
        pstr->buf[0] = '\0';
    }
}

/**
 * 字符串扩容
 * @param  str    字符串
 * @param  addlen 扩容量
 * @return 预先分配两倍的存储空间是没有必要的，
 * TODO 扩容算法有问题，我认为没有必要进行两倍扩容，太浪费存储空间
 */
static string *stringExpand(string **str, size_t addlen) {
    size_t len = stringLen(*str);
    size_t curFree = stringAvail(*str);
    size_t lenNew = 0;

    if (curFree >= addlen) { //有足够的容量直接返回
        return *str;
    }

    lenNew = len + addlen;
    if (lenNew < STRING_MAX_PREALLOC) {//扩容要扩容两倍?
        lenNew *= 2;
    } else {
        lenNew += STRING_MAX_PREALLOC;
    }
    printf("New len :%zu \n", lenNew);
    string *strNew = (string *)realloc(*str, sizeof(string) + lenNew + 1);
    if (NULL == strNew) {
        printf("strNew NULL \n");
        return NULL;
    } else  if (strNew != *str) {
        printf("strNew NULL \n");
        return NULL;
    }

    strNew->size = lenNew;
    return strNew;
}

void stringIncrLen(string *str, int incr) {
    assert(str->len + incr + 1 < str->size);

    str->len += incr;
    str->buf[str->len] = '\0';
}

string* stringCatLen(string **str, const void *t, size_t len) {
    size_t lenCur = stringLen(*str);
    string *strNew = stringExpand(str, len);
    if (!strNew) {
        printf("NULL %s %zu \n", t, len);
        return NULL;
    }

    memcpy(strNew->buf+lenCur, t, len);
    strNew->len = lenCur + len;
    strNew->buf[strNew->len] = '\0';

    return strNew;
}

string* stringCat(string **str, const void *t) {
    return stringCatLen(str, t, strlen(t));
}

string* stringCatString(string **str, string *str2) {
    return stringCatLen(str, str2->buf, str2->len);
}


string* stringCpyLen(string **str, const void *t, size_t len) {
    string *pstrNew = NULL;
    if ((*str)->size < len+1) {
        pstrNew = stringExpand(str, len-(*str)->len);
        if (!pstrNew) {
            return NULL;
        }

        assert(pstrNew == *str);
    }
    memcpy((*str)->buf, t, len);
    (*str)->len = len;
    (*str)->buf[len] = '\0';
    return (*str);
}
string* stringCpy(string **str, const void *t) {
    return stringCpyLen(str, t, strlen(t));
}


string* stringCatSprintf(string **str, const char *fmt, ...) {
    va_list ap;
    va_list ap_cpy;
    int buf_len = 16;
    char *buf = NULL;

    va_start(ap, fmt);
    while (1) {
        if (!(buf = malloc(buf_len))) {
            return NULL;
        }

        buf[buf_len-2] = '\0';
        va_copy(ap_cpy, ap);
        vsnprintf(buf, buf_len, fmt, ap_cpy);
        if (buf[buf_len-2] != '\0') {
            free(buf);
            buf_len +=2;
            continue;
        }
        break;
    }
    va_end(ap);

    string *pstrNew = stringCat(str, buf);
    assert(pstrNew == *str);
    free(buf);
    return *str;

}

string* stringSprintf(string **str, const char *fmt, ...) {
    va_list ap;
    va_list ap_cpy;
    int buf_len = 16;
    char *buf = NULL;

    va_start(ap, fmt);
    while (1) {
        if (!(buf = malloc(buf_len))) {
            return NULL;
        }

        buf[buf_len-2] = '\0';
        va_copy(ap_cpy, ap);
        vsnprintf(buf, buf_len, fmt, ap_cpy);
        if (buf[buf_len-2] != '\0') {
            free(buf);
            buf_len +=2;
            continue;
        }
        break;
    }
    va_end(ap);

    string *pstrNew = stringCpy(str, buf);
    assert(pstrNew == *str);
    free(buf);
    return *str;
}

void stringTrim(string *str, const char *cset) {
    char *start, *end, *sp, *ep;

    sp = start = str->buf;
    ep = end = str->buf+str->len-1;

    while (sp <= end && strchr(cset, *sp))
        sp++;
    while (ep >= start && strchr(cset, *ep))
        ep--;

    size_t len = (sp > ep) ? 0 : ((ep-sp) + 1);
    if (str->buf != sp) {
        memmove(str->buf, sp, len);
    }
    str->len = len;
    str->buf[len] = '\0';
}

/**
 * 截取字符串，只保留固定部分的字符串，其余部分过滤掉
 * @param  str   原来的字符串
 * @param  start 开始坐标
 * @param  end   结束坐标下一个，比如，取第二三个字符   [1, 3]
 * @return
 */
int stringRange(string *str, int start, int end) {
    size_t lenCur = str->len;
    if (start < 0 || start > (lenCur-1)) {
        return -1;
    } else if (end < 0 || end > lenCur) {
        return -1;
    } else if (start > end) {
        return -1;
    }

    size_t lenNew = end - start;
    memmove(str->buf, str->buf+start, lenNew);
    str->buf[lenNew] = '\0';
    str->len = lenNew;
    return 0;
}

void stringToLower(string *str) {
    int i ;
    for (; i < str->len; i++) {
        str->buf[i] = tolower(str->buf[i]);
    }
}

void stringToUpper(string *str) {
    int i =0;
    for (; i < str->len; i++) {
        str->buf[i] = toupper(str->buf[i]);
    }
}

/**
 * 字符串比较函数
 * @param  str1 字符串1
 * @param  str2 字符串2
 * @return
 */
int stringCmp(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t minlen = len1 < len2 ? len1 : len2;

    int cmp = memcmp(str1, str2, minlen);
    if (0 == cmp) {
        return len1 - len2;
    }
    return cmp;
}

/**
 * 字符串切割
 * @param  buf   [description]
 * @param  field [description]
 * @param  n     [description]
 * @param  ifs   [description]
 * @return       [description]
 */
int     stringExplode(unsigned char *buf, unsigned char *field[], int n, const unsigned char * ifs) {
    return 0;
}
