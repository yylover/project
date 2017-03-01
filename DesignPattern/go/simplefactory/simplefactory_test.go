package simplefactory

import "testing"

func TestTypeA(t *testing.T) {
	a := NewConcreteProduct("a")
	name := a.Name()
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
