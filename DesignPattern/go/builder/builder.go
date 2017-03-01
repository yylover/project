package builder

//Builder 构造器接口类
type Builder interface {
	PartA() string
	PartB() string
	PartC() string
	getResult()
}

//Director 类
type Director struct {
	builder Builder
	part1   string
	part2   string
	part3   string
}

//NewDirector Director类简单工厂方法
func NewDirector(builder Builder) *Director {
	return &Director{
		builder: builder,
	}
}

// Construct 初始化方法
func (d *Director) Construct() {
	d.part1 = d.builder.PartA()
	d.part2 = d.builder.PartB()
	d.part3 = d.builder.PartC()
}

//Builder1 构造器1
type Builder1 struct {
}

func (d *Builder1) PartA() string {
	return "Builder1_A"
}

func (d *Builder1) PartB() string {
	return "Builder1_B"
}

func (d *Builder1) PartC() string {
	return "Builder1_C"
}

func (d *Builder1) getResult() {
}

//Builder2 构造器2
type Builder2 struct {
}

func (b *Builder2) PartA() string {
	return "Builder2_A"
}

func (b *Builder2) PartB() string {
	return "Builder2_B"
}

func (b *Builder2) PartC() string {
	return "Builder2_C"
}

func (b *Builder2) getResult() {
}
