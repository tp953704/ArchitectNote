package main

import (
	singletong "designPattern/1_singleton"
	observer "designPattern/2_observice"
	decorator "designPattern/3_decorator"
	patternDesign "designPattern/base"
)

var PatternFactory = map[string]func() patternDesign.DesignPattern{
	"singleton": func() patternDesign.DesignPattern {
		return &singletong.SingleTon{}
	},
	"observer": func() patternDesign.DesignPattern {
		return &observer.ObeserverPattern{}
	},
	"decorator": func() patternDesign.DesignPattern {
		return &decorator.DecoratorPattern{}
	},
}

func getPattern(t string) patternDesign.DesignPattern {
	if factory, ok := PatternFactory[t]; ok {
		return factory()
	}
	return nil
}
func main() {
	pattern := getPattern("decorator")
	pattern.Handler()

}
