package main

import (
    "sync"
    "time"
)

/*
利用 GODEBUG来深入了解调度器的行为，可以告诉用户程序的行为
> go build ..
> GOMAXPROCS=1 GODEBUG=schedtrace=1000 ./scheduler
> GOMAXPROCS=1 GODEBUG=scheddetail=1,schedtrace=1000 ./scheduler


SCHED 0ms: gomaxprocs=2 idleprocs=0 threads=4 spinningthreads=1 idlethreads=0 runqueue=0 [0 0]
SCHED 1003ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 2013ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 3023ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 4034ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 5040ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 6040ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 7041ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 8047ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 9052ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 10058ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
SCHED 11058ms: gomaxprocs=2 idleprocs=2 threads=4 spinningthreads=0 idlethreads=2 runqueue=0 [0 0]
main loop quit

    * 1003ms: 从程序开始执行的毫秒数
    * gomaxprocs: 配置的处理器数。go并发模型中的P,会通过os的线程绑定到一个特定的物理处理器
    * threads: 运行期配置的线程数
    * idlethreads: 空闲的线程数
    * idleprocs: 空闲的处理器数
    * runqueue: 在全局run队列中goroutine数目，目前所有的goroutine移动到本地run队列。
    * [0 0] 本地run队列中的goroutine数目，

> GOMAXPROCS=1 GODEBUG=schedtrace=1000,scheddetail=1 ./scheduler

*/

var counter int
var lock sync.Mutex

func main() {
    counter = 0

    var wg sync.WaitGroup
    for i := 0; i < 10; i++ {
        go work(&wg, i)
        wg.Add(1)
    }

    wg.Wait()

    print("main loop quit\n")
    print(counter)
}

func addCounter() {
    lock.Lock()
    counter++
    lock.Unlock()
}

func work(wg *sync.WaitGroup, idx int) {
    // time.Sleep(time.Second)
    for i := 0; i < 1000; i++ {
        time.Sleep(time.Millisecond * 10)
        addCounter()
    }
    time.Sleep(time.Millisecond * 100)
    wg.Done()
}
