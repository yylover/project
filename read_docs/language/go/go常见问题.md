1. 简式的变量声明仅可以在函数内部使用
    t := 1
2. 偶然变量隐藏
    go tool vet -shadow your_file.go。
3. 不使用显示类型，无法使用nil来初始化变量
    nil标识interface, 函数,maps, slices channels零值，如果不指定变量类型，将不能指定为nil.

4. slices maps 使用nil
    nil的slices添加元素没有问题，但是map将会panic
```
    var a []int = nil
    a = append(a, 1)
    a = append(a, 2)
    a = append(a, 3)

    var b map[string]string = nil
```

5. Map容量，可以在创建时指定容量，但是无法使用cap
6. 字符串不为nil
    var x string = nil //error
7. array 值类型
8. slice Array 遍历
```
for _, v := range x {
    fmt.Println(v) //prints a, b, c
}
```
9. 检测map中是否存在某个值
```
if _,ok := x[ "two" ]; !ok {
    fmt.Println( "no entry" )
}
```
10. string只读类型，无法修改, string和[]byte之间的转换
```
x := "text"

xbytes := [] byte (x)

xbytes [0 ] = 'T'
y := string(xbytes)
```
11. string 索引，返回的byte值
12. 字符串长度,len(str)返回byte数量，utf8.RuneCountInString(str) 返回unicode长度
13. 多行的Slice,Array Map语句，加,
```
x := [] int {
1 ,
2 ,
}
```
14. 内建的数据结构不是线程安全的

15. 自增、自减，没有前置版本的操作
16. 按位NOT ^d
17. 有活动的goroutine不应该退出，常见使用WaitGroup变量。
18. 已经关闭的Channel发送，会panic
19. nil的channel 读写操作会永久阻塞
20. 要关闭htttp响应
```
resp, err := http.Get( "https://api.ipify.org?format=json" )
if err != nil {
    fmt.Println(err)
    return
}

defer resp.Body.Close() //ok, most of the time :-)
```
21. panic中恢复
recover()函数可以用于获取/拦截panic。仅当在一个defer函数中被完成时，
22. 更新map值，不能直接更新单个struct值
