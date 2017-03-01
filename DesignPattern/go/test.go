package main

import (
	"fmt"
	"sync"
)

var once sync.Once

func func1() {
	fmt.Println("func1")
}

func func2() {
	fmt.Println("func2")
}

func doprint1() {
	once.Do(func1)
	once.Do(func2)
}

func main() {
	doprint1()
	a := make([]int, 5, 10)
	a = append(a, 45)
	//
	// a := []int{1, 2, 3, 4, 5}
	fmt.Printf("abc %d %d %v \n", len(a), cap(a), a)
}
