package singletongo

import "sync"

type AppConfig struct {
	Url      string
	Password string
}

var instance *AppConfig
var once sync.Once

func GetAppConfig() *AppConfig {
	once.Do(
		func() {
			instance = &AppConfig{
				Url:      "url",
				Password: "pass",
			}
		},
	)
	return instance
}
