package main

import (
	"fmt"
	"time"
)

var t int32
var x map[int]int

func setT() {
	for i := 0; i < 100; i++ {
		x[i] = i
	}
}

func getT() {
	for i := 0; i < 1000; i++ {
		fmt.Printf("%d\n", x[i])
	}
}

func main() {
	t = 0
	x = make(map[int]int)

	go setT()
	// go setT()
	go getT()
	go getT()
	go getT()
	go getT()

	s := 159
	time.Sleep(time.Second)
	fmt.Printf("map: %d %d\n", t, int64(s))
}
