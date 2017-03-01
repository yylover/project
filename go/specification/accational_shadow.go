package main

import "fmt"

func main() {
	var a []int = nil
	a = append(a, 1)
	a = append(a, 2)
	a = append(a, 3)
	fmt.Printf("slice :%v\n", a)

	var b map[string]string = make(map[string]string, 99)
	b["name"] = "uang" //panic
	fmt.Printf("map: %d\n", len(b))
}
