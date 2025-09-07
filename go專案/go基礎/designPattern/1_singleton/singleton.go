package singletongo

import "fmt"

type SingleTon struct {
}

func (pattern *SingleTon) Handler() {
	cfg := GetAppConfig()

	fmt.Println(cfg.Password)
}
