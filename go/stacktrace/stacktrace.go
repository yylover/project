package main

/*
* 传递切片参数，实际要传递三个地址，一个是切片内数组地址，一个是长度，一个是切片容量。
    传递字符串，一个是字符串地址，一个是字符串长度。
* 对于方法, 第一个要传递对象的指针。
* 数的参数可以填充到一个单一word 中时，参数的数值会打包到一起

### example1

    >goroutine 1 [running]:
    > main.example1(0xc420037ed8, 0x2, 0xa)

### example2
    > goroutine 1 [running]:
    > main.example2(0xc420037ed8, 0x2, 0xa, 0x10666e5, 0x8, 0x2)

### example3
    > goroutine 1 [running]:
    > main.(*trace).example3(0xc420037ed8, 0xc420037ed8, 0x2, 0xa, 0x10667c5, 0x8, 0x4)

### example4
    函数的参数可以填充到一个单一word 中时，参数的数值会打包到一起

    >goroutine 1 [running]:
    >main.example4(0xc417010001)
### example 5
    遵循字节对齐，前三个一个地址，第四个一个地址
    goroutine 1 [running]:
    main.example5(0x10001, 0x17)

### example 6
    > goroutine 1 [running]:
    > main.example6(0x3, 0x100, 0x17)
*/

func main() {
	slice := make([]string, 2, 10)
	// example1(slice)

	// example2(slice, "example2", 2)
	//
	var t trace
	t.example3(slice, "example3", 4)

	// example4(true, false, true, 23)

	// example5(true, false, true, 23)

	example6(3, false, true, 23)
}

func example1(slice []string) {
	panic("print stack trace")
}

func example2(slice []string, str string, i int) {
	panic(str + " print stack trace")
}

type trace struct{}

func (t *trace) example3(slice []string, str string, i int) {
	panic(str + " print stack trace")
}

func example4(b1, b2, b3 bool, i uint8) {
	panic("print stack trace")
}

func example5(b1, b2, b3 bool, i int) {
	panic("print stack trace")
}

func example6(b1 int, b2, b3 bool, i int) {
	panic("print stack trace")
}
