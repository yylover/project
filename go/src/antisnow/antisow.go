package antisnow

import (
	"sync/atomic"
	"time"
)

type AntiSnower struct {
	curLoad     uint32
	accessLimit uint32
	quitChan    chan bool
	ticker      *time.Ticker
	//notify      chan bool
}

func NewAntiSnower(limit uint32) *AntiSnower {
	as := &AntiSnower{
		accessLimit: limit,
		quitChan:    make(chan bool),
		ticker:      time.NewTicker(time.Second),
		//notify:      make(chan bool),
	}
	go as.Go()

	return as
}

func (as *AntiSnower) Go() {
	for {
		select {
		case <-as.ticker.C:
			//if as.curLoad > as.accessLimit {
			//	as.notify <- true
			//} else {
			//
			//}
			atomic.StoreUint32(&as.curLoad, 0)
		case <-as.quitChan:
			//break 不能跳出两个循环
			return
		}
	}
}

func (as *AntiSnower) Add() bool {
	if as.curLoad > as.accessLimit {
		return false
	}

	atomic.AddUint32(&as.curLoad, 1)
	return true
}

//func (as *AntiSnower) Notify() chan bool {
//	return as.notify
//}

func (as *AntiSnower) GetCurload() uint32 {
	return as.curLoad
}

func (as *AntiSnower) GetAccessLimit() uint32 {
	return as.accessLimit
}

func (as *AntiSnower) SetAccessLimit(limit uint32) {
	atomic.StoreUint32(&as.accessLimit, limit)
}

func (as *AntiSnower) Close() {
	close(as.quitChan)
	//close(as.notify)

	as.ticker.Stop()
}
