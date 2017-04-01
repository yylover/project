### concurrency parr

#### concurrency 并发

#### paralell


### go scheduler

为甚需要开发golang的调度器？
    1. Thread有自己的信号掩码，CPU affinity,但很多对go程序是累赘的。
    2. golang的垃圾回收需要所有的goroutine停止，这样使得内存在一致状态，如果系统调度来实现，会有大量的线程停止工作。

用户空间线程和内核空间线程之间的映射关系,有三种模型:
    * N:1, n个用户空间线程运行在一个系统线程。context切换快，但无法有效利用多核
    * 1:1, 可以有效利用多核资源，但是上下文切换慢，因为需要陷入系统。
    * M:N, (golang)，可以在任意多个os线程上调度任意多个goroutine, 但增加了调度难度

### golang 调度实体
    * M: 代表真正的系统线程, 由os管理
    * P: 代表调度上下文, processor, 数量是由GOMAXPROCS设定的,它代表了真正的并发度，即有多少个goroutine可以同时进行。
    * G: 代表Goroutine, 包含栈信息、命令指针。

### 调度实例
    http://7jpqwg.com1.z0.glb.clouddn.com/67f09d490f69eec14c1824d939938e14_b.jpg

    1. 如图，有两个物理线程，每个M有一个context p, 每个也有正在运行的goroutine
    2. 灰色的goroutine 是等待调度的，P 维护这个队列，称为runqueue.

    http://7jpqwg.com1.z0.glb.clouddn.com/f1125f3027ebb2bd5183cf8c9ce4b3f2_b.jpg
    1. 为什么维护多个上下文P: 当一个os线程被阻塞时（何时阻塞？），P可以转投另一个os线程。如上图， M0陷入阻塞时，P转而在OS线程M1上运行，调度器保证有足够的线程来运行context p;
    2. M1 可能是被创建的，也可能是从线程缓存中取出的。
    3. M0 返回时，它尝试获取一个context p来运行goroutine,如果没有获取到，就把goroutine放到global runqueue中，然后自己进入线程缓存。context 周期性的检查global runqueue。

    http://7jpqwg.com1.z0.glb.clouddn.com/31f04bb69d72b72777568063742741cd_b.jpg
    1. 另一种情况是一个的G很快执行完成，这时这个P会去其他的上下文那里获取任务，一般拿run queue 的一半。
