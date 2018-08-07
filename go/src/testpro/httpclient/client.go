package httpclient

import (
	"context"
	"fmt"
	"net"
	"net/http"
	"time"
)

func main() {
	res, err := http.Get("http://localhost/")
	if err != nil {
		fmt.Println("Get ERror : ", err)
		return
	}
	defer res.Body.Close()

}

func Get() {

	transport := http.Transport{
		Proxy: http.ProxyFromEnvironment,
		DialContext: (&net.Dialer{
			Timeout:   30 * time.Second,
			KeepAlive: 30 * time.Second,
			DualStack: true,
		}).DialContext,
		MaxIdleConns:          100,
		IdleConnTimeout:       90 * time.Second,
		TLSHandshakeTimeout:   10 * time.Second,
		ExpectContinueTimeout: 1 * time.Second,
		MaxIdleConnsPerHost:   200,
		ResponseHeaderTimeout: 29,
		DisableCompression:    true,
	}

	client := http.Client{
		Transport: &transport,
	}

	req, _ := http.NewRequest("POST", "http://some.url", nil)
	req.WithContext(context.Background())
	client.Do(req)

	resp, err := client.Get("http://some.url")

	if err, ok := err.(net.Error); ok && err.Timeout() {
		fmt.Println("get timeout : ", err)
	}
	fmt.Println(resp, err)
}
