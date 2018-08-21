package main

import (
	"runtime"
	"time"
)

/**
	小的对象直接存储，不要用指针
 */
const capcity = 500000
var d interface{}

func value() interface{} {
	m := make(map[int]int, capcity)
	for i := 0; i < capcity;i++ {
		m[i] = i
	}
	return  m
}

func pointer() interface{} {
	m := make(map[int] *int, capcity)
	for i := 0; i < capcity; i++ {
		v := i
		m[i] = &v
	}
	return m
}


func main() {
	//d = pointer()
	d = value()
	for i := 0; i < 20; i++ {
		runtime.GC()
		time.Sleep(time.Second)
	}
}