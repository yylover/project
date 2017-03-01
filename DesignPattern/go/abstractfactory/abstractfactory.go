package abstractfactory

//ProductA 产品A接口
type AbstractProductA interface {
	Use() string
}

type ProductA1 struct {
}

func (p *ProductA1) Use() string {
	return "ProductA1_Use"
}

type ProductA2 struct {
}

func (p *ProductA2) Use() string {
	return "ProductA2_Use"
}

//ProductB 产品A接口
type AbstractProductB interface {
	Eat() string
}

type ProductB1 struct {
}

func (p *ProductB1) Eat() string {
	return "ProductB1_Eat"
}

type ProductB2 struct {
}

func (p *ProductB2) Eat() string {
	return "ProductB2_Eat"
}

//AbstractFactory 抽象工厂接口类
type AbstractFactory interface {
	createProductA() AbstractProductA
	createProductB() AbstractProductB
}

//ConcreteFactoryA 具体工厂A
type ConcreteFactoryA struct {
}

func (c *ConcreteFactoryA) createProductA() AbstractProductA {
	return &ProductA1{}
}

func (c *ConcreteFactoryA) createProductB() AbstractProductB {
	return &ProductB1{}
}

//ConcreteFactoryB 具体工厂B
type ConcreteFactoryB struct {
}

func (c *ConcreteFactoryB) createProductA() AbstractProductA {
	return &ProductA2{}
}

func (c *ConcreteFactoryB) createProductB() AbstractProductB {
	return &ProductB2{}
}
