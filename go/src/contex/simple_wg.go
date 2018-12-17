package main

import (
    "sync"
    "time"
    "fmt"
    "context"
)

/*
`refer-
    [1] http://www.flysnow.org/2017/05/12/go-in-action-go-context.html
    [2]
 */

//使用wg来等待routine完成
func wgControl() {
    var wg sync.WaitGroup

    wg.Add(2)
    go func() {
        time.Sleep(3 * time.Second)
        fmt.Println("1号完成")
        wg.Done()
    }()
    go func() {
        time.Sleep(2 * time.Second)
        fmt.Println("2号完成")
        wg.Done()
    }()
    wg.Wait()
    fmt.Println("好了，大家都干完了，放工")
}

//通知goroutine退出
//局限性是只能通知一个退出，如果有很多个改怎么办，如果一层层无穷的goroutine呢
func notifyRoutineQuit() {
    stop := make(chan bool)

    go func() {
        for {
            select {
            case <-stop:
                fmt.Println("退出信号，停止")
            default:
                fmt.Println("goroutine 监控中")
                time.Sleep(time.Second * 2)
            }
        }
    }()

    time.Sleep(time.Second * 5)
    fmt.Println("notify quit")

    stop <- true
    time.Sleep(time.Second * 2)
    fmt.Println("quit")
}

//context 控制单个goroutine
func simpleContext() {
    ctx, cancel := context.WithCancel(context.Background())
    go func(ctx context.Context) {
        for {
            select {
            case <-ctx.Done():
                fmt.Println("quit")
                return
            default:
                fmt.Println("groutine监控中")
                time.Sleep(time.Second * 2)
            }
        }
    }(ctx)

    time.Sleep(time.Second * 10)
    fmt.Println("notify cancel")
    cancel()

    time.Sleep(time.Second * 2)
}

func watch(ctx context.Context, name string) {
    for {
        select {
        case <-ctx.Done():
            fmt.Println(name,"监控退出，停止了...")
            return
        default:
            fmt.Println(name,"goroutine监控中...")
            time.Sleep(2 * time.Second)
        }
    }
}

//context 控制多个goroutine
func ctxMultiControl() {
    ctx, cancel := context.WithCancel(context.Background())
    go watch(ctx, "监控1")
    go watch(ctx, "监控2")
    go watch(ctx, "监控3")

    time.Sleep(time.Second * 10)
    fmt.Println("notify cancel")
    cancel()

    time.Sleep(time.Second * 2)
}

//接口定义
/**
    Deadline() (deadline time.Time, ok bool) //返回是否设置截止时间
    Done
 */

func main() {
    //simpleContext()
    ctxMultiControl()
}
