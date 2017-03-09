package main

import "fmt"

type Week interface {
	Today()
	Next(*DayContext)
}

type DayContext struct {
	today Week
}

func NewDayContext() *DayContext {
	return &DayContext{
		today: &Sunday{},
	}
}

func (d *DayContext) Today() {
	d.today.Today()
}

type Sunday struct {
}

func (*Sunday) Today() {
	fmt.Printf("Sunday")
}

func (*Sunday) Next(ctx *DayContext) {
	ctx.today = &Monday{}
}

type Monday struct {
}

func (*Monday) Today() {
	fmt.Printf("Monday")
}

func (*Monday) Next(ctx *DayContext) {
	ctx.today = &Tuesday{}
}
