package main

import (
	"flag"
	"fmt"
	"net"
)
//http://colobu.com/2016/10/19/Go-UDP-Programming/

var host = flag.String("host", "", "host")
var port = flag.Int("port", 8323, "port")

func main() {
	fmt.Println("hello")
	flag.Parse()

	srcAddr := &net.UDPAddr{IP: net.IPv4zero, Port: 0}
	dstAddr := &net.UDPAddr{IP: net.ParseIP(*host), Port: *port}

	udpconn, err := net.DialUDP("udp", srcAddr, dstAddr)
	if err != nil {
		panic(err)
		return
	}
	defer udpconn.Close()
	udpconn.Write([]byte("hello"))
}

