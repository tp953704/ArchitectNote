package decorator

type Beverage interface {
	Desc() string
	Cost() int64
}

type Coffee struct {
}

func (coffee *Coffee) Desc() string {
	return "coffee"
}

func (coffee *Coffee) Cost() int64 {
	return 64
}

type MikeDecorator struct {
	B Beverage
}

func (m *MikeDecorator) Desc() string {
	return m.B.Desc() + "mike"
}
func (m *MikeDecorator) Cost() int64 {
	return m.B.Cost() + 10
}

func WithMike(b Beverage) Beverage {
	return &MikeDecorator{B: b}
}

// type ExtraFeature func(Beverage) Beverage

func WithCaramel(b Beverage) Beverage {
	return &CaramelDecorator{be: b}
}

type CaramelDecorator struct {
	be Beverage
}

func (c *CaramelDecorator) Desc() string {
	return c.be.Desc() + " + 焦糖"
}

func (c *CaramelDecorator) Cost() int64 {
	return c.be.Cost() + 22
}

type DecoratorPattern struct {
}

func (pattern *DecoratorPattern) Handler() {
	coffee := &Coffee{}
	println("咖啡 %s,cost %d", coffee.Desc(), coffee.Cost())

	mikeCoffee := WithMike(coffee)
	println("咖啡 %s,cost %d", mikeCoffee.Desc(), mikeCoffee.Cost())

	caramelCoffee := WithCaramel(mikeCoffee)
	println("咖啡 %s,cost %d", caramelCoffee.Desc(), caramelCoffee.Cost())

}
