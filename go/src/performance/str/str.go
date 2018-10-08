package main

import (
	"fmt"
	"strings"
    "os"
    "runtime/pprof"
    "reflect"
)

func test1() {
	s := "hello, world!"
	b := []byte(s)
	fmt.Println(s, b)
}

func main() {
	s := strings.Repeat("abc", 100)
	f, err := os.Create("test")
	if err != nil {
	    fmt.Println("err:", err.Error())
	    return
    }
	pprof.StartCPUProfile(f)
	defer pprof.StopCPUProfile()

	for i := 0; i < 10000; i++ {
		//b := str2bytes(s)
		//_ := bytes2str(b)
		s := []byte(s)
		_ = string(s)
		reflect.ValueOf(s)
	}

	//fmt.Println(b, s2)
}
