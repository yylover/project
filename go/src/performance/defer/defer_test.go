package main

import (
	"sync"
	"testing"
	"github.com/eapache/queue"
	"os"
)

var m sync.Mutex

func httpCurl() {

}

func call() {
	m.Lock()
	m.Unlock()
}

func deferCall() {
	m.Lock()
	defer m.Unlock()
}

//错误的调用，变成了串行
func download() {
	m.Lock()
	defer m.Unlock()

	url := queue.Pop()
	httpCurl(url)
}

//错误，隐式的资源泄露
func analysis() {
	files := listDir("./log")
	for _, name := range files {
		f, err := os.Open(name)
		if err != nil {
			continue
		}
		defer f.Close()
	}
}

func BenchmarkCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		call()
	}
}


func BenchmarkDeferCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		deferCall()
	}
}