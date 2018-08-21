package jsonbench

//import (
//    "testing"
//    jsoniter "github.com/json-iterator/go"
//    "github.com/golang/protobuf/proto"
//)

//func BenchmarkSprintf(b *testing.B){
//    num:=10
//    b.ResetTimer()
//    for i:=0;i<b.N;i++{
//        fmt.Sprintf("%d",num)
//    }
//}
//func BenchmarkFormat(b *testing.B){
//    num:=int64(10)
//    b.ResetTimer()
//    for i:=0;i<b.N;i++{
//        strconv.FormatInt(num,10)
//    }
//}
//func BenchmarkItoa(b *testing.B){
//    num:=10
//    b.ResetTimer()
//    for i:=0;i<b.N;i++{
//        strconv.Itoa(num)
//    }
//}
//
//func BenchmarkJson(b *testing.B) {
//    n := News{
//        Id : "idvalue",
//        Title: "usb",
//        Articletype: "56",
//    }
//    b.ResetTimer()
//    for i:=0;i<b.N;i++{
//        json.Marshal(n)
//    }
//}

//func BenchmarkDJson(b *testing.B) {
//    n := News{
//        Id : "idvalue",
//        Title: "usb",
//        Articletype: "56",
//    }
//    var djson = jsoniter.ConfigCompatibleWithStandardLibrary
//
//    b.ResetTimer()
//    for i:=0;i<b.N;i++{
//        data, _ := djson.Marshal(n)
//        djson.Unmarshal(data, &n)
//    }
//}
//
//func BenchmarkPbMarshal(b *testing.B) {
//    n := NewsPb{
//        Id : "idvalue",
//        Title: "usb",
//        Articletype: "56",
//    }
//    b.ResetTimer()
//    for i:=0;i<b.N;i++{
//        data := proto.MarshalTextString(&n)
//        proto.UnmarshalText(data, &n)
//    }
//}
//
