package main



import (
	"flag"
	"fmt"
	"net"
	"time"
)

var host = flag.String("host", "", "host")
var port = flag.String("port", "333", "port")

func main() {
	fmt.Println("hello")
	flag.Parse()

	tcpconn, err := net.Dial("tcp", *host+":"+*port)
	if err != nil {
		panic(err)
		return
	}
	defer tcpconn.Close()

	done := make(chan string)
	go handleRead(tcpconn, done)
	go handleWrite(tcpconn, done)

	<-done
	<-done

}

func handleRead(conn net.Conn, done chan string) {
	for i := 0; i < 10; i++ {
		conn.SetWriteDeadline(time.Now().Add(time.Second))
		conn.Write([]byte("hello\r\n"))
	}

	done <- "Sent"
}

func handleWrite(conn net.Conn, done chan string) {

	for i := 0; i < 10; i++ {
		conn.SetReadDeadline(time.Now().Add(time.Second))
		buf := make([]byte, 1024)
		reqlen, err := conn.Read(buf)
		if err != nil {
			fmt.Println("read error", err)
			break
		}

		fmt.Println("read len:", reqlen, string(buf[:reqlen-1]))
	}
	done <- "write"
}

