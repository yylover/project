package main

import (
	"fmt"
	"testing"
)

type Tester interface{
	Test(int)
}

type Data struct{
	x int
}

func (d *Data) Test(x int) {
	d.x += x
}

func call(d *Data) {
	d.Test(100)
}

func ifaceCall(t Tester) {
	t.Test(100)
}

func main() {
	d := &Data{x:100}
	call(d)
	ifaceCall(d)

	fmt.Printf("%v", d)
}


func BenchmarkCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		call(&Data{x:100})
	}
}

func BenchmarkIfaceCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ifaceCall(&Data{x:100})
	}
}
