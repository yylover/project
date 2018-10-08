package skiplist

import (
    "math/rand"
)


/*
http://dsqiu.iteye.com/blog/1705530
https://redisbook.readthedocs.io/en/latest/internal-datastruct/skiplist.html
http://km.oa.com/articles/show/380797?kmref=dailymail_headline&jumpfrom=daily_mail
 */

const(
    MAX_LEVEL = 32
    ZSKIPLIST_P = 0.25

)

type zskiplist struct {
    header, tail *zskiplistNode
    length int64
    level int
}

type zskiplistLevel struct {
    forward *zskiplistNode
    span int //标识当前指针跨越多少节点
}

type zskiplistNode struct {
    //ele 存放加点数据
    ele string
    score float64
    backward *zskiplistNode
    level []*zskiplistLevel
}

type zset struct {
    //dict
    //zskiplist *zsl;
    zsl *zskiplist
}

func CreateZslNode(level int, score float64, value string) *zskiplistNode{
    node := &zskiplistNode{
        score: score,
        level: make([]*zskiplistLevel, level),
        ele : value,
    }
    return node
}

//创建初始化节点
func zslCreate() *zskiplist{
    zsl := &zskiplist{
        level:1,
        length:0,
        header:CreateZslNode(MAX_LEVEL, 0, ""),
        tail:CreateZslNode(MAX_LEVEL, 0, ""),
    }
    return zsl
}

func randomLevel() int {
    level := 1
    for rand.Float32() < 0.25 {
        level += 1
    }
    return level
}

//插入节点
func ZslInsert(zsl *zskiplist, score float64, value string) {

}