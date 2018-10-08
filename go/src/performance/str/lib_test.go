package main

import (
	"testing"
	"strings"
)

var s = strings.Repeat("a", 1000)

func test() {
	b := []byte(s)
	_ = string(b)
}

func test2() {
	b := str2bytes(s)
	_ = bytes2str(b)
}

func BenchmarkOriginal(b *testing.B) {
	for i := 0; i < b.N; i++ {
		test()
	}
}

func BenchmarkStrlib(b *testing.B) {
	for i := 0; i < b.N; i++ {
		test2()
	}
}