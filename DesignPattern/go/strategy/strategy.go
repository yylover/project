package main

import "fmt"

type PaymentContext struct {
	Name, CardID string
	Money        int
	payment      PaymentStrategy
}

func NewPaymentContext(name, cardid string, money int, payment PaymentStrategy) *PaymentContext {
	return &PaymentContext{
		Name:    name,
		CardID:  cardid,
		Money:   money,
		payment: payment,
	}
}

type PaymentStrategy interface {
	Pay(*PaymentContext)
}

type Cash struct {
}

func (*Cash) Pay(ctx *PaymentContext) {
	fmt.Printf("Pay %d to %s by cash", ctx.Money, ctx.Name)
}

type Back struct{}

func (*Back) Pay(ctx *PaymentContext) {
	fmt.Printf("Pay %d to %s by bank account", ctx.Money, ctx.Name)
}
