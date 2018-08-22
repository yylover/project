package signal

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"
)

var (
	signals = []os.Signal{
		syscall.SIGTERM,
		syscall.SIGINT,
		syscall.SIGQUIT,
		syscall.SIGUSR1,
		syscall.SIGUSR2,
		syscall.SIGKILL, //不能捕获
	}
)

const (
	SIGTERM = iota
	SIGINT
	SIGQUIT
	SIGUSR1
	SIGUSR2
	SIGKILL //不能捕获
)

type SignalCatcher struct {
	quitChan   chan bool
	sigChan    chan os.Signal
	handlerMap map[os.Signal]func()
}

func NewSignalCatcher() *SignalCatcher {
	sc := &SignalCatcher{
		quitChan:   make(chan bool),
		handlerMap: make(map[os.Signal]func()),
		sigChan:    make(chan os.Signal),
	}

	return sc
}

func (this *SignalCatcher) RegisterHandler(fn func(), sigs ...int) error {

	for _, index := range sigs {
		if index > len(signals) {
			return fmt.Errorf("signal cannot register : %d", index)
		}

		sig := signals[index]
		this.handlerMap[sig] = fn
	}
	return nil
}

func (this *SignalCatcher) Close() {
	signal.Stop(this.sigChan)
	close(this.quitChan)
}

func (this *SignalCatcher) Go() {
	signal.Notify(this.sigChan, signals...)

	for {
		select {
		case sig, more := <-this.sigChan:
			if more {
				if fn, ok := this.handlerMap[sig]; ok {
					fn()
				}
			}

		case <-this.quitChan:
			return

		}
	}

}
