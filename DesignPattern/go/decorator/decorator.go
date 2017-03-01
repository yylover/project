package main

import "fmt"

type Component interface {
	Calc() int
}

type ConcreteComponent struct {
}

func (*ConcreteComponent) Calc() int {
	return 0
}

type MulDecorator struct {
	Component
	num int
}

func WarpMulDecorator(c Component, num int) Component {
	return &MulDecorator{
		Component: c,
		num:       num,
	}
}

func (d *MulDecorator) Calc() int {
	return d.Component.Calc() * d.num
}

type AddDecorator struct {
	Component
	num int
}

func WarpAddDecorator(c Component, num int) Component {
	return &AddDecorator{
		Component: c,
		num:       num,
	}
}

func (d *AddDecorator) Calc() int {
	return d.Component.Calc() + d.num
}

func main() {
	c := &ConcreteComponent{}
	d1 := WarpMulDecorator(c, 3)
	d2 := WarpAddDecorator(c, 4)

	fmt.Printf("Mul decorator : %d\n", d1.Calc())
	fmt.Printf("Mul decorator : %d\n", d2.Calc())
}
