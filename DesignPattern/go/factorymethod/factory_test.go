package simplefactory

import "testing"

func TestTypeA(t *testing.T) {
	a := &CreatorA{}
	name := a.CreateProduct()
    if istyp
	if name != "ConcreteProductA" {
		t.Fatal("type a test failed")
	}
}

func TestTypeB(t *testing.T) {
	b := NewConcreteProduct("b")
	name := b.Name()
	if name != "ConcreteProductB" {
		t.Fatal("type b test failed")
	}
}
