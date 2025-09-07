package observe

type Obeserver interface {
	Notify(price float64)
}

type Analysist struct {
	name string
}

func (a *Analysist) Notify(price float64) {
	println("%s 新股價 :%f", a.name, price)
}

type StockMarket struct {
	Price     float64
	name      string
	observers []Obeserver
}

func (s *StockMarket) register(o Obeserver) {
	s.observers = append(s.observers, o)
}
func (s *StockMarket) setPrice(price float64) {
	for _, observer := range s.observers {
		observer.Notify(price)
	}
}

type ObeserverPattern struct {
}

func (pattern *ObeserverPattern) Handler() {
	bob := &Analysist{
		name: "bob",
	}

	ben := &Analysist{
		name: "ben",
	}

	stock1 := &StockMarket{
		Price: 100,
		name:  "0050",
	}

	stock1.register(bob)
	stock1.setPrice(111)

	stock1.register(ben)
	stock1.setPrice(1112)
}
