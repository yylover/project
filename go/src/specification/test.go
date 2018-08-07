package main

import "fmt"

var value map[int32]string
var aChan chan int

func setValue(a, b int32) {
	for i := a; i <= b; i++ {
		value[i] = fmt.Sprintf("Value %d\n", i)
	}
	aChan <- 1
}

func getValue(a, b int32) {
	for i := a; i <= b; i++ {
		fmt.Printf("Value %d\n", i)
	}
	aChan <- 1
}

func main2() {
	aChan = make(chan int)
	value = make(map[int32]string, 200001)
	for index := 0; index < 20000; index++ {
		value[int32(index)] = fmt.Sprintf("Value %d", int32(index))
	}

	go setValue(1, 1000)
	go setValue(1001, 2000)
	go setValue(1, 1000)

	<-aChan
	<-aChan
}
