package jsonbench

import (
    "testing"
    "encoding/json"
    "github.com/pquerna/ffjson/ffjson"
    "github.com/json-iterator/go"
)

type News struct {
    Id                    string `json:"id,omitempty"`
    Title                 string `json:"title"`
    Articletype           string `json:"articletype"`
    Src                   string `json:"src"`
    PubTime               string `json:"pubtime,omitempty"`
    Url                   string `json:"url,omitempty"`
    ShortUrl              string `json:"short_url,omitempty"`
    BigImg                string `json:"bigimg,omitempty"`
    Flag                  string `json:"flag"`
    Cid                   string `json:"cid,omitempty"`
    Vid                   string `json:"vid,omitempty"`
    Duration              string `json:"duration,omitempty"`
    Reason                string `json:"reason,omitempty"`
    ReasonFlag            string `json:"reason_flag,omitempty"`
    PushCommentCount      int    `json:"pushCommentCount,omitempty"`
    kurl                  string
    Chlid                 string                 `json:"chlid,omitempty"`
    Thumbnails            []interface{}          `json:"thumbnails"`
    ThumbnailsQQnews      []interface{}          `json:"thumbnails_qqnews"`
    ThumbnailsQQnewsAttr  map[string]interface{} `json:"thumbnails_qqnews_attr,omitempty"`
    ThumbnailsQQnewsPhoto []interface{}          `json:"thumbnails_qqnews_photo,omitempty"`
    ThumbnailsQQnewsVideo string                 `json:"thumbnails_qqnews_video"`
    Commentid             string                 `json:"commentid,omitempty"`
    PicShowType           int                    `json:"picShowType"`
    VideoId               string                 `json:"videoId,omitempty"`
    VideoDuration         int                    `json:"videoDuration,omitempty"`
    VideoWatchCount       int                    `json:"videoWatchCount,omitempty"`
    Timestamp             int64                  `json:"timestamp"`
    Abstract              string                 `json:"abstract,omitempty"`
    Source                string                 `json:"source"`
    Scheme                string                 `json:"scheme"`
    ChlName               string                 `json:"chlname"`
    ChlIcon               string                 `json:"chlicon"`
    ShareUrl              string                 `json:"share_url"`
    HasVideo              int                    `json:"hasVideo,omitempty"`
    PureVideo             int                    `json:"pureVideo,omitempty"`
    ImageCount            int                    `json:"imagecount"`
    Vexpr                 map[string]string      `json:"vexpr,omitempty"`
    AlgVersion            uint32                 `json:"alg_version"`
    SeqNo                 string                 `json:"seq_no"`
    AlgInfo               string                 `json:"alginfo,omitempty"`
    ActionList            map[string]interface{} `json:"action_list,omitempty"`
    VideoHideUrl          string                 `json:"video_hide_url,omitempty"`
}

func Benchmark_Original(b *testing.B){
    b.ResetTimer()
    for i:=0;i<b.N;i++{
        t := News{}
        datamap := map[string]interface{}{}
        data, _ := json.Marshal(t)
        json.Unmarshal(data, datamap)
    }
}

func Benchmark_ffjson(b *testing.B){
    b.ResetTimer()
    for i:=0;i<b.N;i++{
        t := News{}
        datamap := map[string]interface{}{}
        data, _ := ffjson.Marshal(t)
        ffjson.Unmarshal(data, datamap)
    }
}

func Benchmark_djson(b *testing.B){
    b.ResetTimer()
    for i:=0;i<b.N;i++{
        t := News{}
        datamap := map[string]interface{}{}
        var djson = jsoniter.ConfigCompatibleWithStandardLibrary
        data, _ := djson.Marshal(t)
        djson.Unmarshal(data, datamap)
    }
}