/*****************************************************************************
Copyright: 2017~2030 yangqiang personal
File name: con.h
Description: 配置文件读取，
Author: yangqiang
Version: 1.0
Date:
History:

demo :
    1. 配置文件都是key value形式，value为int或string, block形式{},block里面也是key value形式


双链接表结构和操作逻辑声明:
1. 空链表:head tail 都为NULL, length=0
2. free 指针用于释放value的值，不需要释放可以填写NULL
3. match 用于比较value的值，如果没有设置，直接使用== 比较

1. 疑问:函数指针？实现

*****************************************************************************/

#ifndef __CONF_H__
#define __CONF_H__

#define CONF_TYPE_ENTRY 1
#define CONF_TYPE_BLOCK 2

#define MAX_LINE 1023  //最大行数

typedef struct conf_value {
    void *value;
    unsigned int type;
} conf_value_t;

typedef struct conf_t {
    hash_t *ht;
} conf_t;

typedef struct conf_entry {
    char *value;
    struct conf_entry *next;
} conf_entry_t;

typedef struct conf_block {
    conf_t block;
    struct conf_block *next;
} conf_block_t;

int conf_init(conf_t *conf, const char *filename);
int conf_get_int_value(conf_t *conf, const char *key, int def);
char *conf_get_str_value(conf_t *conf, const char *key, int def);
conf_block_t conf_get_block(conf_t *conf, char *key);
void conf_free(conf_t *conf);
void conf_dump(conf_t *conf);

#endif
