package main

import "testing"

func BenchmarkTest(b *testing.B) {
	for i := 0; i < b.N; i++ {
		data := make(chan int, bufsize)
		done := make(chan struct{})

		_ = test(data, done)
	}
}

func BenchmarkTestBlock(b *testing.B) {
	for i := 0; i < b.N; i++ {
		data := make(chan[block] int, bufsize)
		done := make(chan struct{})

		_ = testBlock(data, done)
	}
}