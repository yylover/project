package main

//代理模式用于延迟处理操作或者在进行实际操作前后进行其它处理。

//Subject 对象接口
type Subject interface {
	Do() string
}

//RealSubject 实际对象
type RealSubject struct {
}

//Do 实际动作
func (*RealSubject) Do() strint {
	return "real"
}

//Proxy 关键代码，采用组合的方式实现
type Proxy struct {
	real RealSubject
}
