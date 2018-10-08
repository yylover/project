package main

import (
	"fmt"
)

const capacity = 1024

func array() [capacity]int {
	var d [capacity]int

	for i := 0; i < len(d); i++ {
		d[i] = 1
	}

	return d
}

func slice() []int {
	d := make([]int, capacity)

	for i := 0; i < len(d); i++ {
		d[i] = 1
	}

	return d
}

func main() {
	fmt.Println(array())
	fmt.Println(slice())
}
