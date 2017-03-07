package main

import (
	"errors"
	"flag"
	"fmt"
	"os"
	"strings"
	"time"
)

//example 自定义value
/*
type Value interface {
	String() string
	Set(string) error
}*/
type internal []time.Duration

func (i *internal) String() string {
	return fmt.Sprint(*i)
}

func (i *internal) Set(value string) error {
	if len(*i) > 0 {
		return errors.New("interval flag already set")
	}
	for _, dt := range strings.Split(value, ",") {
		fmt.Println(dt)
		duration, err := time.ParseDuration(dt)
		if err != nil {
			return err
		}
		*i = append(*i, duration)
	}
	return nil
}

func main() {

	//example 1:默认的flags使用
	a := flag.Bool("tls", false, "if enable the tls encryption")
	b := flag.Float64("version", 2.2, "the version of app")

	//example 2:两个变量共享同一个值,必须有相同的默认值，系统会保证只初始化最新的值
	const (
		defaultGopher = "pocket"
		usage         = "the variety of gopher"
	)
	var gopherType string
	flag.StringVar(&gopherType, "gopher_type", defaultGopher, usage)
	flag.StringVar(&gopherType, "g", "defaultGopher", usage+"(shorthand)")

	//example 3: 自定义flag类型  -deltaT 300ms,20ns
	var internalFlag internal
	flag.Var(&internalFlag, "deltaT", "list of interval date")

	//example 4: 使用FLagSet解析
	var internalFlag2 internal
	flagset := flag.NewFlagSet("mq", flag.ExitOnError)
	c := flagset.Bool("tls", false, "if enable the tls encryption")
	d := flagset.Float64("version", 2.2, "the version of app")
	flagset.StringVar(&gopherType, "gopher_type", defaultGopher, usage)
	flagset.StringVar(&gopherType, "g", "defaultGopher", usage+"(shorthand)")
	flagset.Var(&internalFlag2, "deltaT", "list of interval date")
	flagset.Parse(os.Args[1:])

	fmt.Printf("version :%s\n", flagset.Lookup("version").Value.String())
	fmt.Printf("g :%s\n", flagset.Lookup("g").Value.String())

	flag.Parse()
	fmt.Printf("%v\n", os.Args[1:])
	fmt.Printf(" %v %v %v\n", *a, *b, gopherType)
	fmt.Printf(" %v %v %v\n", *c, *d, gopherType)
	fmt.Printf("date: %v", internalFlag2)

}
