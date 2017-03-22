package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

/*
typedef uint64          uintptr;

*/

/*数据类型分为静态类型和底层类型，相对于以下代码中的变量b来说，byte是它的静态类型，uint8是它的底层类型*/
func byteType() {
	var b byte = 'D'
	fmt.Printf("output :%v\n", reflect.TypeOf(b).Kind())
	/*uint8*/
}

/** rune 是int32 的别名 */

/** string
string 底层是c struct 实现，str使用byte类型而不是rune类型，因为golang for循环是针对字节循环,
如果有必要，可以转成rune切片或用range来代替
struct string {
    byte *str;
    intgo len;
};
**/
func printString() {
	var str1 = "hi, 欢迎来~"
	p := (*struct {
		str uintptr
		len int
	})(unsafe.Pointer(&str1))

	fmt.Printf("%+v \n", p)
}

/*
   Slice 底层也是一个struct
   struct Slice {
       byte* array; //存放实际的数据
       uintgo len; //实际元素的个数
       uintgo cap; //容量
    };

    make 函数可以用于对slice map channel 对象的初始化操作
    nil 寻常结构不能与nil进行比较，nil与interface 或指针比较

    使用array 或slice 的切片操作初始化另外一个slice时，这时新的slice的array地址是指向当前的array或
    slice的，对slice进行赋值操作会改变原来的array,如果append,要看append后容量是否超出原来的值，如果超出
    会重新分配，不会改变原来的值
*/
func sliceType() {
	var slice = make([]int32, 5, 10)
	p := (*struct {
		array uintptr
		len   int
		cap   int
	})(unsafe.Pointer(&slice))
	fmt.Printf("%+v \n", p)
}

func slicePtrTest() {
	var arr1 = []int{1, 2, 3, 4, 5}
	var arr2 = arr1[2:]
	var arr3 = arr1[2:4]

	fmt.Println(len(arr2), cap(arr2)) /** 2 3 容量是3**/
	fmt.Println(len(arr3), cap(arr3)) /** 3 3 容量是3**/
	var arr2Append = append(arr2, 100)
	fmt.Println(arr1, arr2, arr2Append) //[1 2 3 4 5] [3 4 5] [3 4 5 100]

	var arr4 = arr1[2:4]
	var arr4Append = append(arr4, 100, 200)
	fmt.Println(arr1, arr4, arr4Append) //[1 2 3 4 5] [3 4] [3 4 100 200]

	var arr3Append = append(arr3, 100)
	fmt.Println(arr1, arr3, arr3Append) //[1 2 3 4 100] [3 4] [3 4 100]
}

/* interface
interface 是一个结构体，包括两个成员，一个指向数据的指针，一个包含成员的类型信息。
 struct Iface {
      Itab *tab;
      void *data;
 };
 struct Eface {
      Type *type;
      void *data;
  };

  struct Itab {
      InterfaceType *inter;
      Type *type;
      Itab *link;
      int32 bad;
      int32 unused;
      void (*fun[])(void);
  };
*/

/* map
 底层数据结构是一个哈希表，但是与C++区别的是它是一个无序的哈希表。
struct {
  uintgo  count;
  uint32  flags;
  uint32  hash0;
  uint8   B;
  uint8   keysize;
  uint8   valuesize;
  uint16  bucketsize;

  byte    *buckets;
  byte    *oldbuckets;
  uintptr nevacuate;
};
*/
func mapTest() {
	var m = make(map[string]int32, 10)

	m["hello"] = 123

	p := (*struct {
		count int
		flags uint32
		hash0 uint32
		B     uint8

		keysize    uint8
		valuesize  uint8
		bucketsize uint16
		buckets    uintptr
		oldbuckets uintptr
		nevacuate  uintptr
	})(unsafe.Pointer(&m))

	fmt.Printf("output: %+v\n", p)

}

func main() {

	slicePtrTest()
	byteType()
	printString()
	sliceType()
	mapTest()
}
