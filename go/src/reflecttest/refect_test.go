package main

import (
    "testing"
    "github.com/json-iterator/go"
    "reflect"
    //"fmt"
    "strings"
)

func getTagName(tag string) string {
    tags := strings.Split(tag, ",")
    if len(tags) > 0 {
        return tags[0]
    }
    return ""
}

func InMapSI(m map[string]int, key string) bool {
    if m == nil || len(m) == 0 {
        return false
    }

    if _, ok := m[key]; ok {
        return true
    }
    return false
}

func Benchmark_marshaljson(b *testing.B){

    n := News{
        Id : "idvalue",
        Title: "usb",
        Articletype: "56",
    }

    fields := map[string] int {
        "id" : 1,
        "title": 1,
    }

    b.ResetTimer()

    for i:=0;i<b.N;i++{
        d := map[string]interface{}{}
        elem := reflect.ValueOf(&n).Elem()
        elemT := reflect.TypeOf(&n).Elem()
        for i := 0; i < elem.NumField(); i++ {
            //fmt.Println(elemT.Field(i).Tag.Get("json"))
            //fmt.Println(elemT.Field(i).Name)
            //fmt.Println(elem.Field(i).Interface())
            tagname := getTagName(string(elemT.Field(i).Tag.Get("json")))
            if tagname != "" && tagname != "-" && InMapSI(fields, tagname) {
                d[elemT.Field(i).Name] = elem.Field(i).Interface()
            }
        }
    }
}

func Benchmark_djson(b *testing.B){
    n := News{
        Id : "idvalue",
        Title: "usb",
        Articletype: "56",
    }

    fields := map[string] int {
        "id" : 1,
        "title": 1,
    }

    b.ResetTimer()
    for i:=0;i<b.N;i++{
        datamap := map[string]interface{}{}
        var djson = jsoniter.ConfigCompatibleWithStandardLibrary
        data, _ := djson.Marshal(n)
        djson.Unmarshal(data, datamap)

        for k, _ := range datamap {
            if _, ok := fields[k]; !ok && k != "url" {
                delete(datamap, k)
            }
        }
    }
}