package antisnow

import (
	"runtime"
	"time"
)

/**
  TODO : gc 时间
  完全按照时间来调度，是否对增加gc压力
*/

//每隔一段时间检查gc时间，进行gc
type MemoryMonitor struct {
	quitChan chan bool
	ticker   *time.Ticker
}

func NewMemoryMonitor() *MemoryMonitor {
	as := &MemoryMonitor{
		quitChan: make(chan bool),
		ticker:   time.NewTicker(time.Second),
	}
	go as.Go()

	return as
}

func (as *MemoryMonitor) Go() {
	var memstat runtime.MemStats
	for {
		select {
		case <-as.ticker.C:

			runtime.ReadMemStats(&memstat)
			if time.Now().UnixNano()-int64(memstat.LastGC) > int64(time.Millisecond*500) {
				runtime.GC()
			}

		case <-as.quitChan:
			//break 不能跳出两个循环
			return
		}
	}
}

func (as *MemoryMonitor) Close() {
	close(as.quitChan)
	as.ticker.Stop()
}
