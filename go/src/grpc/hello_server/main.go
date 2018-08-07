package main

import (
	"fmt"
	"google.golang.org/grpc"
	"grpc/proto"
	"log"
	"net"
	"golang.org/x/net/context"
)

type FuncServer struct {
}

func (this *FuncServer) Hello(ctx context.Context, param *proto.HelloParam) (*proto.HelloReply, error) {
    return nil, fmt.Errorf("hello failed")
    return &proto.HelloReply{"hello", "haha"}, nil
}

func main() {
	//flag.Parse()
	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", 8242))
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	grpcServer := grpc.NewServer()

	proto.RegisterHelloServerServer(grpcServer, &FuncServer{})
	//reflection.Register(grpcServer)
	//TODO tls config
	grpcServer.Serve(lis)
}
