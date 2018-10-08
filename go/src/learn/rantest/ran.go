package main

import (
    "fmt"
    "math/rand"
)


func test() {
    for i := 0; i < 10; i++ {
        fmt.Println(rand.Int()%1000)
    }
}


func main() {

    for i := 0; i < 100; i++ {
        go test()
    }
}