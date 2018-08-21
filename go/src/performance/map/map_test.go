package main

import "testing"

/**
	预先分配容量会节省堆分配和拷贝时间
 */

func test(m map[int]int) {
	for i := 0; i < 10000;i++ {
		m[i] = i
	}
}

func BenchmarkMap(b *testing.B) {
	for i := 0; i < b.N; i++ {
		m := make(map[int]int)
		test(m)
	}
}

func BenchmarkCapMap(b *testing.B) {
	for i := 0; i < b.N; i++ {
		m := make(map[int]int, 10000)
		test(m)
	}
}