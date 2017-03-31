package main

func main() {
	slice := make([]string, 2, 10)
	// example1(slice)

	// example2(slice, "example2", 2)
	//
	var t trace
	t.example3(slice, "example3", 4)
}

func example(slice []string) {
	panic("print stack trace")
}

func example2(slice []string, str string, i int) {
	panic(str + " print stack trace")
}

type trace struct{}

func (t *trace) example3(slice []string, str string, i int) {
	panic(str + " print stack trace")
}
