package factorymethod

//ProductParent parent interface
type ProductParent interface {
	Name() string
}

//ConcreateProductA implement interface ProductParent
type ConcreteProductA struct {
}

func (*ConcreteProductA) Name() string {
	return "ConcreteProductA"
}

//ConcreateProductB inplement interface ProductParent
type ConcreteProductB struct {
}

//ConcreteProductB
func (*ConcreteProductB) Name() string {
	return "ConcreteProductB"
}

type CreatorParent interface {
	CreateProduct() ProductParent
}

type CreatorA struct {
}

func (*CreatorA) CreateProduct() ProductParent {
	return &ConcreteProductA{}
}

type CreatorB struct {
}

func (*CreatorB) CreateProduct() ProductParent {
	return &ConcreteProductB{}
}
