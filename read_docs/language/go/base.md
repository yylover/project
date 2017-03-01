
### 变量

变量是一块存储区域的命名

#### 变量声明
```
func vardeclare() {
	var v1 int      //
	var v2 string   //
	var v0 [10]int
	var v3 []int    //数组切片
	var v5 struct { //？
		f int
	}
	var v6 *int            //指针
	var v7 map[string]int  //map
	var v8 func(a int) int //函数

	//可以同时声明多个变量
	var (
		vv1 int
		vv2 string
	)
}
```
####  变量初始化
声明时进行初始化var,不再是关键元素
```
var v1 int = 10  //
var v2 = 10      //编译器可以推导v2类型
v3 := 10         // 编译器可以推导v3类型
//这里让Go语言看起来像动态语言，实际上，Go是强类型语言（静态语言）。
//匿名变量
_, _ , nickname := GetName()//func GetName()(firstname, lastname, nickname)
```

#### 变量赋值
变量的赋值，赋值与初始化是不同的概念
```
//变量的多重赋值
var i = 10
var j = 20
i, j = j, i
```

### 常量
常量是指编译期间就已知且不可改变的值。常量可以是数值类型(包括整型、
浮点型和复数类型)、布尔类型、字符串类型等。

```
func constant() {
	//字面型常量
	-13
	true
	"foo"
	3.2+12i //复数类型常量

	//常量定义，采用const
	const PI float64 = 3.1415926
	const (
		size int64 = 1024
		eof = -1
		mask = 1 << 3//也可以是编译期间运算的常量表达式
	)

	//下一句会发生编译错误，因为常量赋值是编译器行为，而GetEnv是运行期才拿到
	const Home = os.GetEnv("HOME")

	//预定义常量
	true false itoa//itoa可以被编译器修改的常量，每一个const关键字出现时置为0，每出现一次，加1
	const (
		a = 1 << itoa //1
		b = 1 << itoa //2
		c = 1 << itoa //4
	)
	const mask = 1 << 3

	//枚举 Go并不支持常规语言的enum关键字
	const (
		Sunday = iota
		Monday
		...
	)
}
```

### 类型

```
//1. bool true|false
//2. 整型 int8 uint8 byte int16 uint16 int uint int32 uint32 int64 uint64 uintptr
//3. 浮点 float32 float64
//4. 复数 complex64 complex128
//5. 字符串 string
//6. 字符类型： rune
//7. 错误类型： error

//符合类型
//1. 指针
//2. 数组
//3. 切片
//4. map
//5. chan
//6. struct
//7. interface
```
#### bool

```
var b1 bool
b1 = false
b1 = (1 == 2)
b1 = bool(1) //错误,bool不接受其他类型值，不支持自动或强制转换
```

#### 数值
int int32在Go语言是两种不同的类型，编译器不会做自动类型转换，需要自己进行转换
```
value2 = int32(value3) //编译通过
//运算： + - * / %
//比较： > < >= <= == !=
//位运算: x << y x >> y x^y x&y  x|y ^x
```

#### 浮点

```
//float32 float64相当于c语言的float double类型
var f1 float64 = 1.0001
var f2 float64 = 1.0002
fvalue2 := 12.0 //自动推断为float64的值

//比较，因为浮点数不是精确的表达方式
isEqual := math.Dim(f1, f2) < 0.0001
```
#### 复数

```
value1 := 3.2 + 12i
value2 := complex(3.2, 3.4)
rel := real(value1) //实部
img := imag(z) //虚部
```

#### 字符串
字符串是不可改变的值

```
var s1 string = "test"
s1 = s1 + "abcd"   // 字符串拼接
c1 = s1[2]         //取字符，
lenth := len(s1)   //长度
s1 = `\w+`         //反引号，不转义，常用于正则表达式

//字符遍历 字节数组方式
for i := 0; i < n; i++ {
	ch := str[i]
}

//Unicode字符rune,每个字符是rune,代表单个Unicode字符
str := "hello, 语言"
for i, ch := range str {
    fmt.Println(i, ch)//ch的类型为rune
}
```

#### 字符类型

字符有两种，byte(uint8类型) rune (unicode类型)

#### 数组
1. 数组就是指一系列同一类型数据的集合。数组也是不可变类型
2. 数组是值类型, 每次传递都将产生一份副本。
```
var arr1 [32]int //字节数组
var arr2 [10]*float64 //指针数组
var arr3 [3][5]int //二维数组
var arr4 [2][2][4]float64 //三维数组
t := len(arr4) //长度

//初始化
arr1 = [32]int{1,2,3,4}
//临时结构体数组
structArray := []struct{
	name string
	age int
}{{"time", 18}, {"yang", 24}}

//数组遍历
for i := 0; i < len(arr1); i++ {
	fmt.Println(arr1[i])  // [] 获取数组内元素
}
for i, v := range arr1 {
	fmt.Println(v)
}
```

#### 切片
切片的数据结构可以抽象为：指向原数组的指针；数组切片中元素的个数；数组切片已经分配的存储空间

```
//创建方式：1 处于数组arrayname[first, last] 2 直接创建
var myArray [10]int = [10]int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
var mySlice []int = myArray[:5]
myslice = myArr[:] 所有元素
myslice = myArr[:5] 前5个元素
//make 直接创建
mySlice1 := make([]int, 5)       //初始五个元素，并设置为0
mySlice2 := make([]int, 5, 10)   //初始长度5，预留10个元素存储空间，即：len=5,cap=10(10包括前五个)
mySlice3 := []int{1, 2, 3, 4, 5} //初始化5个元素

//遍历方式与数组相同，有两种方式
fmt.Println("len(mySlice):", len(mySlice)) //len 是当前存储元素个数
fmt.Println("cap(mySlice):", cap(mySlice)) //cap 数组切片剩余的空间大小

//动态增加元素
mySlice4 := append(mySlice3, 6, 7, 8)    //append ,append开始位置不会占用之前的,不会改变之前的切片
mySlice5 := append(mySlice3, mySlice2...) //将一个数组切片追加到另一个切片末尾，不加...会有编译错误

//基于数组切片创建切片
mySlice6 := mySlice5[:5]

//copy 如果前后两个切片个数不同，那么安装较小的切片进行复制 ， 假设mySlice1 3个元素，mySlice2 5个元素
copy(mySlice1, mySlice2) //只复制前三个,会改变slice1
copy(mySlice2, mySlice1) //只复制三个
```

#### map
map是一堆键值对的未排序集合。
```
var myMap map[string] PersonalInfo      //声明
myMap = make(map[string] PersonalInfo)  //创建
myMap = make(map[string] PersonalInfo, 10) //指定存储能力
myMap["123"] = PersonalInfo{"1", "Jack", "Room"} //赋值
delete(myMap, "123")    //元素删除,如果不存在，什么都不发生，如果key=nil,则panic
value, ok := myMap["123"] //元素的查找,ok==true,则存在
```
### 流程控制
1. 条件 if else  else if
2. 选择 switch case select
3. 循环 for range
4. 跳转 goto

```
if a = 5; a < 5 {
	return false
} else {
	return true
}

// switch
switch i {
case 0:
	fmt.Println(0)
case 1:
	fallthrough //添加后才会紧接执行下一个case
case 3:
	fmt.Println(3)
default:
	fmt.Println("Default")
}

//如果省略switch后的表达式，与if ...else...逻辑相同
switch {
case 0 <= num && num <= 3:
	fmt.Println("0-3")
case 4 <= num && num <=6:
	fmt.Println("4-6")
}

//循环只支持for
for i := 0; i < 10; i++ {

}
//无限循环
for {
	sum ++
	if sum > 100 {
		break
	}
}
//条件表达式支持多重赋值， break可以选择中断哪一个循环
for i, j : =0, len(a) -1 ; i < j; i, j = i+1, j-1 {
	for k := 0; k < j; k++ {
		break JLoop
	}
}
JLoop:

//跳转
HERE:
i++
if i < 10 {
	goto HERE
}
```

### 函数

```
//func func_name(参数列表)(返回值列表)
func Add(a, b int) (ret int, err error) {//参数列表多个相邻的参数类型相同，可以省略前面的类型声明
	if a < 0 || b < 0 {
		err = errors.New("Should be non-negative numbers")
		return //可以直接对返回值设置
	}
	return a + b, nil
}

//访问控制：对于函数，类型和变量，小写字母开头只在本包内可见，大写字母开头的才在包外使用；

//不定参数
//myFunc(1, 2, 3) 调用方式
func myFunc(args ...int) {
	for _, arg := range args {

	}

	//不定参数的传递
	myfunc3(args...)
	myfunc3(args[1:]...)
}

//任意类型不定参数
//args.(type) 在switch 中类型判断，interface{}具体的一种类型判断host, ok := host.(string)
func MyPrintf(args ...interface{}) {
	for _, arg := range args {
		switch arg.(type) {
		case int:
			fmt.Println(arg, " is an int value")
		case string:
			fmt.Println(arg, " is an string value")
		default:
			fmt.Println(arg, " is Unknown value")
		}
	}
}

//匿名函数与闭包
/*
闭包：可以包含自由（未绑定到特定对象）变量的代码块，这些变量不再这个代码块中或者任何全局上下文中定义，而是在定义代码块的环境中定义。
意义：闭包可以作为函数对象或者匿名函数， 函数可以作为第一级对象，存储到变量中作为参数传递。能被函数动态创建和返回
匿名函数:不需要定义函数名的一种函数实现方式。函数可以赋值被变量或直接执行(花括号后面跟参数列表表示函数调用)
*/
//有疑问?????
func main() {
	var j int = 5
	a := func()(func()) {
		var i int = 10
		return func() {
			fmt.Printf("i, j: %d, %d\n", i, j)
		}
	}()
	a() // 10 5
	j *= 2
	a() // 10 10
}

```
### 错误处理

```
错误处理流程: 当在一个函数执行过程中调用panic()函数时,正常的函数执行流程将立终止,但函数中之前使用defer关键字将开始执行，
之后该函数将返回到调用函数,并导致逐层向上执行panic流程,直到所属的goroutine中所有正在执行的函数被终 。
func CopyFileDemo() {
	srcFile, err := os.Open(src)
	if err != nil {
		return
	}
	defer srcFile.Close()

	//匿名函数
	defer func() {
		//负责的清理工作
		if r := recover(); r := nil {
			fmt.Printf("runtime error caught :%v", r)
		}
		}()

	//func panic(interface{}) 报告运行时错误
	//func recover() interface{} 处理运行时错误或程序错误,用于中止错误处理流程
}

```

## 面向对象编程

类型系统是一门编程语言的基础，典型的类型系统包括以下内容：
1. 基础类型byte int bool float
2. 复合类型:数组、结构体、指针等
3. 可以指向任意对象的类型Any
4. 值语义和引用语义
5. 面向对象
6. 接口

### 指针还是对象形式
```
//可以为任意类型添加方法
type Integer int
func (a Integer) Less(b Integer) bool {
	return a < b
}

//修改原对象的时候，需要使用指针
type Integer int

func (a Integer) Add(b Integer) {
	a += b
}

func (a *Integer) AddP(b Integer) {
	*a += b
}
```

### 值语义还是引用语义

值引用： Go中大多数都是值语义
值语义和引用语义的区别在于赋值。值语义不会影响a的值。
1. 基本类型， byte, int, bool, float32, float64, string
2. 复合类型： array struct 指针
下面四个类型比较特殊，看起来像引用类型
 * 切片 map channel interface, 其实现内部维护一个指针，本身还是值语义
接口:
```
type interface struct{
	data *void
	itab *Itab
}
```
### 结构体
结构体： Go语言中的结构体跟其他语言中的类有相同的地位，其放弃了继承在内的大量面向对象特性，只保留组合

#### 定义和初始化
```
type Rect struct {
	x, y float
	width, height float64
}

//初始化
rect1 := new(Rect)
rect2 := &Rect{}
rect3 := &Rect{0, 0, 100, 200}
rect4 := &Rect{width:100, height: 200} //未显示初始化的被初始化为该类型零值
```

#### 匿名组合
确认的说go也提供了继承，还是通过匿名组合的方式来提供。匿名组合的规则:
    1.派生类没有修改基类方法时，方法被继承；
    2. 派生类调用基类方法的规则:sub.BaseClassName.baseFunc()
    3. 如果派生类与基类函数名相同，基类方法被覆盖。如果想要调用基类版本，还可以调用sub.BaseClassName.baseFunc()
```
type Base struct {
	Name string
}

func (base *Base) Foo() {
	fmt.Println("Base Foo")
}
func (base *Base) Bar() {
	fmt.Println("Base Bar")
}

type Sub struct {
	Base
}

func (sub *Sub) Bar() {
	sub.Base.Bar()
	fmt.Println("Sub Bar")
}

func main() {
	foo := new(Sub)
	//Base Bar
	//Sub Bar
	foo.Bar()
	//Base Foo
	foo.Foo()
```

#### 指针方式组合
继承规则:
1. 派生类创建实例时，需要提供一个额外的基类实例的指针
2. 其他规则与非指针组合方式一样
```
type Job struct {
	Command string
	*log.Logger
}

logger := log.New(logFile, "[info]", log.Ldate|log.Ltime|log.Llongfile)
job := &Job{"programming", logger}
```

### 可见性
包级别，首字母大小写控制

### 接口
接口：非侵入性，一个类只需实现所有函数，就说这个类实现了该接口
接口赋值：对象赋值给接口;接口赋值接口(接口赋值不要求必须等价，如果接口A方法列表是接口B方法列表自己，接口B可以赋值给A)
```
type LessAdder interface {
    Less(b Integer) bool
    Add(b Integer)
}

func (a Integer) Less(b Integer) bool {
    return a < b
}
func (a *Integer) Add(b Integer) {
    *a += b
}

var a Integer = 1
var b LessAddr = &a  //应该使用指针的形式
```

#### 接口查询
查询某个对象是否实现了某个接口
```
var file1 Writer = ...
if file5, ok := file1.(two.IStream); ok {
    //实现了接口，处理逻辑
}

//查询类型
if file6, ok := file1.(*File); ok {
    ...
}

//查询类型
switch v := file.(type) {
case int :
case string:
}
```

#### 接口组合
```
type ReadWriter interface {
	Reader
	Writer
}
```

### Any类型
Any 类型 interface{}


## 并发编程
优雅的并发编程范式，完善的并发支持，出色的并发性能是Go区别于其他语言的特色。
channel是Go语言级别提供的goroutine间的通信方式。可以使用channel在两个或多个goroutine之间传递消息

### 协程
goroutine是Go语言中的轻量级线程实现,由Go运行时(runtime)管理。

### channel
channel是Go语言在语言级别提供的goroutine间的通信方式。channel是进程内的通信方式,因此通过channel传递对象的过程和调 用函数时的参数传递行为比较一致,比如也可以传递指针等

#### 基本语法
```
var chanName chan ElementType
//定义
ch := make(chan int)
ch <- value //数据写入
value := <-ch  //读数据

//select 语法类型switch，每个case必须是IO操作
select {
case <-chan1:
// 如果chan1成功读到数据,则进行该case处理语句
case chan2 <- 1:
// 如果成功向chan2写入数据,则进行该case处理语句
default:
// 如果上面都没有成功,则进入default处理流程
}

//缓冲区
c := make(chan int, 1024)
```
#### 超时机制
加入超时器

#### chan传递

#### 单向chan
```
var ch2 chan<- int //单向写channel
var ch3 <-chan int //单向读channel
close(ch3) //关闭channel
if x, ok := <-ch3; !ok {
	//ch3已经关闭
}
```
#### 关闭chan
```
close(ch)//关闭 channel
x, ok := <-ch //判断channel是否已经关闭
```

#### 多核并行
runtime.GOMAXPROCS(runtime.NumCPU()) //多核并行
runtime.Gosched() //出让时间片

#### 同步

```
var l1 sync.Mutex
var l2 sync.RWMutex
l.Lock()
defer l.Unlock()

var once sync.Once //全局唯一性操作
once.Do(setup) //setup函数只会被执行一次
```

once保证的是全局只执行一次Do()
```
var once sync.Once

func func1() {
	fmt.Println("func1")
}

func func2() {
	fmt.Println("func2")
}

func doprint1() {
	once.Do(func1)
	once.Do(func2)
}

func main() {
	doprint1() //只执行Func1
}
```

### 网络编程

### json

## 安全问题


## 工程管理

### 单元测试

### 性能测试
