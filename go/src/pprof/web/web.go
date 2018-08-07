package main

import "net/http"
import (
    _ "net/http/pprof"
    "time"
    "fmt"
    "strings"
)


func main()  {
    //http.ListenAndServe("0.0.0.0:8082", nil)
    reader:= strings.NewReader("http://v.qq.com/index.html\r\nhttp://v.qq.com/img/1.jpeg")
    req,_ := http.NewRequest("POST","http://refresh.api.hycdn.oa.com:27591/refresh?type=url&plat_ids=0&format=plain", reader)

    DefaultClient := &http.Client{
        Timeout: time.Millisecond * time.Duration(time.Millisecond * 300),
    }
    resp, err := DefaultClient.Do(req)
    fmt.Println(err)
    fmt.Println(resp.Body)
}