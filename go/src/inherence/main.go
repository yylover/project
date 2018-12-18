package main

import "fmt"

/**
go继承有三种:
1. interface
2. struct
3. *struct

 */
type BaseInter interface {
    ShowA()
    ShowB()
}

type Base struct {
    // nothing
    name string
}

func (b *Base) ShowA() {
    fmt.Println(b. name + "showA")
    b.ShowB()
}
func (b *Base) ShowB() {
    fmt.Println(b. name + "showB")
}

type Derived struct {
    Base
}

func (d *Derived) ShowB() {
    fmt.Println(d. name + "Derived showB")
}

type DerivedP struct {
    *Base
}

func (d *DerivedP) ShowB() {
    fmt.Println(d.name + "Derived showB")
}

type DerivedInter struct {
    BaseInter
}
func (d *DerivedInter) ShowB() {
    fmt.Println( "Derived showB")
}


type Mutex struct {
    // nothing
}

func (m *Mutex) Lock() {
    fmt.Println("mutex lock")
}

func (m *Mutex) Unlock() {
    fmt.Println("mutex unlock")
}

type newMutex Mutex

type structMutex struct {
    Mutex
}

func main() {
    m1 := Mutex{}
    m1.Lock()

    //n1 := newMutex{}
    //n1.Lock()      没有Lock()方法

    x1 := structMutex{}
    x1.Lock()

}

func main2() {
    b := Base{}
    b.name = "yang"

    d := Derived{}
    d.ShowA()
    d.ShowB()

    p := DerivedP{&b}
    p.ShowA()
    p.ShowB()
    fmt.Println(&b)

    i := DerivedInter{&b}
    i.ShowA()
    i.ShowB()
    fmt.Println(i.BaseInter.(*Base).name)

}
