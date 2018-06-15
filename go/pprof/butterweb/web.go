package main

import (
    "butterfly"
    "butterfly/server/context"
)


type HelloController struct {
}

func (this *HelloController) Get(ctx *context.WebContext) error {
   ctx.Response.Write([]byte("hello"))
    return nil
}

func (this *HelloController) Post(ctx *context.WebContext) error {
    return this.Get(ctx)
}

func main() {

    butterfly.RegisterHTTPController("/hello", &HelloController{})
    butterfly.Run()
}