package channeltt

import (
	"sync"
	"testing"
	"sync/atomic"
)

func chanCounter() chan int {
	c := make(chan int)
	go func() {
		for x := 1; ; x++ {
			c <- x
		}
	}()

	return c
}

func mutexCounter() func() int {
	var m sync.Mutex
	var x int

	return func() (n int) {
		m.Lock()
		x++
		n = x
		m.Unlock()
		return
	}
}

//单就唯一号生成来说，可以更优化
func atomicCounter() func() int {
	var x int64

	return func() int {
		return int(atomic.AddInt64(&x, 1))
	}
}

func BenchmarkChanCounter(b *testing.B) {
	c := chanCounter()
	b.ResetTimer()

	for i := 0; i < b.N;i++ {
		_ = <- c
	}
}

func BenchmarkMutextCounter(b *testing.B) {
	f := mutexCounter()
	b.ResetTimer()

	for i := 0; i< b.N; i++ {
		_ = f()
	}
}


func BenchmarkAtomicCounter(b *testing.B) {
	f := atomicCounter()
	b.ResetTimer()

	for i := 0; i< b.N; i++ {
		_ = f()
	}
}



