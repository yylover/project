package main

import (
	"fmt"
	"reflect"
)

/**
https://juejin.im/post/5a75a4fb5188257a82110544
 */

type News struct {
	Id          string `json:"id,omitempty"`
	Title       string `json:"title"`
	Articletype string `json:"articletype"`
	Src         string `json:"src"`
	PubTime     string `json:"pubtime,omitempty"`
	Url         string `json:"url,omitempty"`
}

func main() {

	var val interface{} = int64(56)
	fmt.Println("VALUE : ", reflect.ValueOf(val))
	val = 50
	fmt.Println("VALUE : ", reflect.TypeOf(val))
	return

	var t int = 10
	test := map[string]interface{}{}
	test["a"] = "string"
	test["b"] = []string{"slice"}
	test["c"] = map[string]string{"map": "test"}
	test["d"] = make(chan int)
	test["f"] = func(a int) int {
		return a
	}
	test["g"] = &t
	test["h"] = nil

	var c map[string]string
	var d map[string]string = nil
	test["i"] = c
	test["j"] = d

	for k, v := range test {
		//if reflect.ValueOf(v).IsNil() {
		//if reflect.ValueOf(v).Len() == 0 {
		if v == nil {
			fmt.Printf("%v is nil\n", k)
		} else {
			fmt.Printf("%v is not nil\n", k)
		}
	}

	return

	n := News{
		Id:          "idvalue",
		Title:       "usb",
		Articletype: "56",
	}

	elem := reflect.ValueOf(&n).Elem()
	elemT := reflect.TypeOf(&n).Elem()
	for i := 0; i < elem.NumField(); i++ {
		fmt.Println(elemT.Field(i).Tag.Get("json"))
		fmt.Println(elemT.Field(i).Name)
		fmt.Println(elem.Field(i).Interface())
	}

}
