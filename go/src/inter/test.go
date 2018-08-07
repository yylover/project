package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

type data struct {
}

func (d *data) Error() string {
	return " data error "
}

func bad() bool {
	return true
}

func test() error {
	var p *data = nil
	if bad() {
		return p
	}
	return nil
}

func main() {
	var val interface{} = int64(58)
	fmt.Println(reflect.TypeOf(val))
	val = 50
	fmt.Println(reflect.TypeOf(val))

	var tt interface{} = (*interface{})(nil)
	fmt.Println("tt == nil : ", tt == nil)

	var e error = test()

	d := (*struct {
		itab uintptr
		data uintptr
	})(unsafe.Pointer(&e))

	fmt.Println("d  :", d)

	if e == nil {
		fmt.Println("e is nil")
	} else {
		fmt.Println("e is not nil", e.Error())
	}
	fmt.Printf("%V", e)

}
