package main

import "time"


/**
	go build -gcflags "-m" -o test
	，闭包引用原环境变量，导致 y 逃逸到堆上，这必然增加了 GC 扫描和回收对象的数量
 */

func test() {
	x := 100

	go func(a int) {
		a++
		println(a)
	}(x)

	x++
}

func ClosureTest() {
	y := 100
	go func(a int) {
		y++
		println(a)
	}(y)

	y++
}

func main() {
	test()
	ClosureTest()

	time.Sleep(time.Second)
}