package main

import (
	"flag"
	"fmt"
	"net"
	"os"
)

var host = flag.String("host", "", "host")
var port = flag.Int("port", 8323, "port")

func main() {
	fmt.Println("hello")
	flag.Parse()

	udpconn, err := net.ListenUDP("udp", &net.UDPAddr{IP: net.ParseIP(*host), Port:*port})
	if err != nil {
		panic(err)
		return
	}
	defer udpconn.Close()


	data := make([]byte, 1024)
	for {
		n, remoteaddr, err := udpconn.ReadFromUDP(data)
		if err != nil {
			fmt.Println("error reading: ", err)
			os.Exit(1)
		}
		fmt.Println("<%s> %s \n", remoteaddr, data[:n])

		_, err = udpconn.WriteToUDP([]byte("world"), remoteaddr)
		if err != nil {
			fmt.Printf(err.Error())
		}

	}
}

