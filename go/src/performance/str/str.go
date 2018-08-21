package main

import (
	"fmt"
	"strings"
)


func test1() {
	s := "hello, world!"
	b := []byte(s)
	fmt.Println(s, b)
}

func main() {
	s := strings.Repeat("abc", 3)
	b := str2bytes(s)
	s2 := bytes2str(b)
	fmt.Println(b, s2)
}
