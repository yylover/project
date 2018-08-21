package main

import (
	"runtime"
	"time"
)

type X struct {
	data [1<<20]byte
	ptr *X
}

func test() {
	var a, b X
	a.ptr = &b
	b.ptr = &a
	runtime.SetFinalizer(&a, func(*X){println(" a is fianl")})
	runtime.SetFinalizer(&b, func(*X){println(" b is fianl")})
}

func main() {
	for i := 0; i < 100; i++ {
		test()
	}

	for i := 0; i < 10; i++ {
		runtime.GC()
		time.Sleep(time.Second)
	}
}