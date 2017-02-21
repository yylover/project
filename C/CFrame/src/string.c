
#include <string.h>
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
    string *str = calloc(1, sizeof(*str)+len+1);
    if (str == NULL) {
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

string* stringDup(string *str) {
    if (init->buf) {
        return stringNew((const void *) init->buf))
    } else {
        return NULL;
    }
}

/**
 * 释放字符串
 * @param  str
 * @return
 */
void    stringFree(string *str) {
    if (pstr)  {
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
void    stringClear(string *str) {
    if (str) {
        pstr->len = 0;
        pstr->buf[0] = '\0';
    }
}

static string *stringExpand(string **str, size_t addlen) {
    string *strNew = NULL;
    size_t len = stringLen(str);
    size_t size = stringAvail(str);
    size_t lenNew = 0;

    if (size - len -1 >= addlen) {
        return *pstr;
    }

    lenNew = len + addlen;
    if (lenNew < STRING_MAX_PREALLOC) {
        lenNew *= 2;
    } else {
        lenNew += STRING_MAX_PREALLOC;
    }

    strNew = realloc(*str, sizeof(string) + lenNew + 1);
    if (NULL == strNew) {
        return NULL;
    } else  if (strNew != *str) {
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

void    stringResize(string *str, int incr) {

}

string* stringCatLen(string **str, const void *t, size_t len) {
    size_t lenCur = stringLen(str);
    string *strNew = stringExpand(*str, len);
    if (!strNew) {
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

}
string* stringCpy(string **str, const void *t) {
    return stringCpyLen(str, t, strlen(t));
}

string* stringCatSprintf(string **str, const char *fmt, ...) {

}

string* stringSprintf(string **str, const char *fmt, ...) {

}

void    stringTrim(string *str, const char *cset) {
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

int     stringRange(string *str, int start, int end) {
    size_t lenCur = str->len;
    if (start < 0 || start > (lenCur-1)) {
        return -1;
    } else if (end < 0 || end > (lenCur-1)) {
        return -1;
    } else if (start > end) {
        return -1;
    }

    size_t lenNew = end - start + 1;
    memmove(str->buf, str->buf+start, lenNew);
    str->buf[lenNew] = '\0';
    str->size = lenNew;
    str->len = lenNew;
    return 0;
}

void    stringToLower(string *str) {
    int len = str->len;
    for (; i < len; i++) {
        str->buf[i] = tolower(str->buf[i]);
    }
}

void    stringToUpper(string *str) {
    int len = str->len;
    int i =0;
    for (; i < len; i++) {
        str->buf[i] = toupper(str->buf[i]);
    }
}

int     stringCmp(const char *str1, const char *str2) {
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
int     stringExplode(unsigned char *buf, unsigned char *field[], int n, const unsigned char * ifs);
