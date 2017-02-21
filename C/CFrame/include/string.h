#ifndef __STRING_H__
#define __STRING_H__

#define STRING_MAX_PREALLOC (10*1024*1024)

typedef struct string {
    int len;    //实际长度
    int size;   //总空间大小
    char buf[]; //数据开始指针
} string;

string* stringNew(const void *init);
string* stringNewEmpty(void);
string* stringDup(string *str);
void    stringFree(string *str);
void    stringClear(string *str);
void    stringResize(string *str, int incr);
string* stringCatLen(string **str, const void *t, size_t len);
string* stringCat(string **str, const void *t);
string* stringCatString(string **str, string *str2);
string* stringCpyLen(string **str, const void *t, size_t len);
string* stringCpy(string **str, const void *t);

string* stringCatSprintf(string **str, const char *fmt, ...);
string* stringSprintf(string **str, const char *fmt, ...);
void    stringTrim(string *str, const char *cset);
int     stringRange(string *str, int start, int end);
void    stringToLower(string *str);
void    stringToUpper(string *str);
int     stringCmp(const char *str1, const char *str2);
int     stringExplode(unsigned char *buf, unsigned char *field[], int n, const unsigned char * ifs);

#endif
