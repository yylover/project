package main

import (
    "github.com/shirou/gopsutil/process"
    "os"
    "fmt"
)

var ps *process.Process

func mem(n int) {
    if ps == nil {
        p, err := process.NewProcess(int32(os.Getpid()))
        if err != nil {
            panic(err)
        }

        ps = p
    }

    memt, _ := ps.MemoryInfoEx()
    fmt.Println(memt)
    //fmt.Printf("%d. VMS:%d MB, RSS:5d MB\n", n, memt.VMS >> 20, memt.RSS >> 20)
}

func main() {
    mem(1)

    data := new([10][1024*1024]byte)
    mem(2)

    for i := range data {
        for x, n := 0, len(data[i]); x < n; x++ {
            data[i][x]= 1
        }

        mem(3)
    }
}
