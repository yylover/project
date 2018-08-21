package main

import "testing"

func BenchmarkIncrX(b *testing.B) {
	d := struct {
		X int
	}{100}

	for i := 0; i < b.N; i++ {
		incX(&d)
	}
}


func BenchmarkUnsafeIncrX(b *testing.B) {
	d := struct {
		X int
	}{100}

	for i := 0; i < b.N; i++ {
		unsafeIncX(&d)
	}
}


func BenchmarkUnsafeIncrXOnline(b *testing.B) {
	d := struct {
		X int
	}{100}

	for i := 0; i < b.N; i++ {
		unsafeIncXOnline(&d)
	}
}
