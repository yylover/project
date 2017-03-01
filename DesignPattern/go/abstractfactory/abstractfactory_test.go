package abstractfactory

import "testing"

func TestFactoryA(t *testing.T) {
	factory := &ConcreteFactoryA{}

	a := factory.createProductA()
	b := factory.createProductB()

	if a.Use() != "ProductA1_Use" {
		t.Fatal("ProductA1_Use test failed")
	}

	if b.Eat() != "ProductB1_Eat" {
		t.Fatal("ProductA1_Use test failed")
	}
}

func TestFactoryB(t *testing.T) {
	factory := &ConcreteFactoryB{}

	a := factory.createProductA()
	b := factory.createProductB()

	if a.Use() != "ProductA2_Use" {
		t.Fatal("ProductA2_Use test failed")
	}

	if b.Eat() != "ProductB2_Eat" {
		t.Fatal("ProductA2_Use test failed")
	}
}
