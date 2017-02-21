
#include<ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../include/conf.h"


static int str2int(const char *strval, int def) {
    //确实是数字
    if (isdiggit(strval) || (isdiggit(strval+1) && strval[0] == '-')) {
        return atoi(strval);
    }

    //on off|yes no| true false|enable disable| enable disabled 表示的bool
    if (strcasecmp(strval, "on")) {
        return 1;
    } else if (strcasecmp(strval, "off")) {
        return 0;
    } else if (strcasecmp(strval, "yes")) {
        return 1;
    } else if (strcasecmp(strval, "no")) {
        return 0;
    } else if (strcasecmp(strval, "true")) {
        return 1;
    } else if (strcasecmp(strval, "false")) {
        return 0;
    } else if (strcasecmp(strval, "enable")) {
        return 1;
    } else if (strcasecmp(strval, "disable")) {
        return 0;
    } else if (strcasecmp(strval, "enable")) {
        return 1;
    } else if (strcasecmp(strval, "disabled")) {
        return 0;
    }

    return def;
}

static void *key_dup(const void *key) {
    return strdup((char *)key);
}

static int str_key_cmp(const void *key1, const void *key2) {
    return strcmp((char *)key1, (char *)key2);
}

static void free_key(void *key) {
    free(key);
}

static int msd_conf_parse(conf_t *conf, char *resolved_path, FILE*fp, int block) {
    
}

/**
 * 配置文件初始化
 * @param  conf     配置数据结构
 * @param  filename 文件名
 * @return          0 -1
 */
int conf_init(conf_t *conf, const char *filename) {
    FILE *fp;

    char resolved_path[PATH_MAX];

    if (!realpath(filename, resolved_path)) {
        return -1;
    }

    if (!(fp = fopen(filename, "r"))) {
        return -1;
    }

    if (conf_parse(conf, resolved_path, fp, 0) != 0) {
        fclose(fp);
        return -1;
    }
    flose(fp);
    return 0;
}

/**
 * 获取key对应的int值
 * @param  conf 配置文件
 * @param  key  key
 * @param  def  默认值
 * @return      [description]
 */
int conf_get_int_value(conf_t *conf, const char *key, int def) {
    conf_entry_t *ce;
    conf_value_t *cv = (conf_value_t*) hash_get_val(key);

    if (!cv) {
        return NULL;
    } else if (cv->type == CONF_TYPE_ENTRY) {
        ce = cv->value;
    } else if (cv->type == CONF_TYPE_BLOCK) {
        return NULL;
    } else {
        return def;
    }

    if (ce) {
        return str2int(ce->value, def);
    }
    return def;
}

/**
 * 获取key对应的string值
 * @param  conf [description]
 * @param  key  [description]
 * @param  def  [description]
 * @return      [description]
 */
char *conf_get_str_value(conf_t *conf, const char *key, int def) {
    conf_entry_t *ce = NULL;
    conf_value_t *cv = (conf_value_t *) hash_get_val(conf->ht, key);

    if (!cv) {
        return NULL;
    } else if (cv->type == CONF_TYPE_ENTRY) {
        ce = cv->value;
    } else if(cv->type == CONF_TYPE_BLOCK) {
        return NULL;
    } else {
        return def;
    }

    if (ce) {
        return ce->value;
    }
    return def;
}

/**
 * 获取block值
 * @param  conf [description]
 * @param  key  [description]
 * @return      [description]
 * 同一个key对应的值可能是一个链表，只取第一个
 */
conf_block_t conf_get_block(conf_t *conf, char *key) {
    conf_entry_t *ce = NULL;
    conf_value_t *cv = (conf_value_t *) hash_get_val(conf->ht, key);

    if (!cv) {
        return NULL;
    } else if (cv->type != CONF_TYPE_ENTRY) {
        ce = cv->value;
    } else if(cv->type == CONF_TYPE_BLOCK) {
        return NULL;
    } else {
        return def;
    }

    if (ce) {
        return (conf_block_t*)ce->value;
    }
    return def;
}

void conf_free(conf_t *conf) {
    hash_free(conf->ht);
}

void conf_dump(conf_t *conf) {

}
