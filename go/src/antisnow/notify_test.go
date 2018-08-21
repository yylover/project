package antisnow

import (
	"testing"
	"time"
)

func TestAntisnow(t *testing.T) {
	a := NewAntiSnower(100)

	go func() {
		time.Sleep(time.Second)
		for i := 0; i < 100; i++ {
			a.Add()
		}
	}()

	select {
	case <-a.Notify():
		return
	case <-time.After(time.Second * 3):
		t.Failed()
	}
}

func TestAntisnowSafe(t *testing.T) {
	a := NewAntiSnower(100)

	go func() {
		time.Sleep(time.Second)
		for i := 0; i < 99; i++ {
			a.Add()
		}
	}()

	select {
	case <-a.Notify():
		t.Failed()
	case <-time.After(time.Second * 3):
		return
	}
}
