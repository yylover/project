package main

import (
	"google.golang.org/grpc"
	"log"
	"grpc/proto"
    "context"
    "time"
)

func main() {
	conn, err := grpc.Dial("localhost:8242", grpc.WithInsecure())
	if err != nil {
		log.Fatalf("cannot access : ", err.Error())
		return
	}
	defer conn.Close()

	c := proto.NewHelloServerClient(conn)

	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	r, err := c.Hello(ctx, &proto.HelloParam{"yang", "hello world"})
	if err != nil {
	    log.Fatalf("call failed : ", err.Error())
    }

    log.Printf("%v", r)

}
