package simplefactory

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

//NewConcreteProduct simple factory method
func NewConcreteProduct(_type string) ProductParent {
	if _type != "a" && _type != "b" {
		return nil
	}

	if _type == "a" {
		return &ConcreteProductA{}
	}
	return &ConcreteProductB{}
}
