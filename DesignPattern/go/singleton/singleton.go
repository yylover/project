package factorymethod

import "sync"

//Singleton 类
type Singleton struct {
}

var singleInstance *Singleton
var singletonLock sync.Mutex

//GetInstance 单利模式获取实例接口
func GetInstance() *Singleton {
	if singleInstance == nil {
		singletonLock.Lock()
		if singleInstance != nil {
			singleInstance = &Singleton{}
		}
		singletonLock.Unlock()
	}
}
