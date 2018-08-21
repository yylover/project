package signal

import (
	"os"
	"os/signal"
)

type SignalCatcher struct {
	quitChan    chan bool
	sigChan chan os.Signal
	handlerMap map[os.Signal] func()
}

func NewSignalCatcher() *SignalCatcher {
	return &SignalCatcher{
		quitChan: make(chan bool),
	}
}

func (this *SignalCatcher) Close() {
	close(this.quitChan)
}

func (this *SignalCatcher) Go() {
	signal.Notify(this.sigChan,)
}

func (this *SignalCatcher) checkSignal() {
	for {
		select {
		case <- this.quitChan:
			return
		case sig := <-this.sigChan:
			if fn, ok := s.tr

		}
	}
}