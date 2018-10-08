package main

import (
    "runtime"
)

func test() *int {
	x := new(int)
	*x = 0xAABB
	return x
}
func main() {
    runtime.GC()
	println(*test())
}
