package main

import (
	"runtime/debug"
	"time"
)

/**
	map的空间不会主动收缩，
 */

const capacity = 1000000
var dict = make(map[int][100]byte, capacity)

func test() {
	for i:= 0; i < capacity; i++ {
		dict[i] = [100]byte{}
	}

	for k := range dict {
		delete(dict, k)
	}

	//dict = nil
	//取消引用，dict 会释放空间
}


func main() {
	test()

	for i := 0; i < 20; i++ {
		debug.FreeOSMemory()
		time.Sleep(time.Second)
	}
}