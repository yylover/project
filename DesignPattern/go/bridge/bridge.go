package main

import "fmt"

//DrawApi
type DrawApi interface {
	drawCircle(radis float32, x int, y int)
}

//RedCircle implement interface DrawApi
type RedCircle struct {
}

func (*RedCircle) drawCircle(radis float32, x int, y int) {
	fmt.Println("draw read circle")
}

//GreenCircle implement interface DrawApi
type GreenCircle struct {
}

func (*GreenCircle) drawCircle(radis float32, x int, y int) {
	fmt.Println("draw green circle")
}

type Shape struct {
	drawApi DrawApi
}

func NewShap(draw DrawApi) *Shape {
	return &Shape{drawApi: draw}
}

func (s *Shape) draw() {
	fmt.Println("shape draw")
}

type Circle struct {
	Shape
	radius float32
	x      int
	y      int
}

func NewCircle(draw DrawApi) *Circle {
	c := &Circle{}
	c.drawApi = draw
	return c
}

func (c *Circle) draw() {
	c.drawApi.drawCircle(c.radius, c.x, c.y)
}

func main() {
	red := &RedCircle{}

	c := NewCircle(red)
	c.radius = 2.3
	c.x = 2
	c.y = 3

	c.draw()
}
