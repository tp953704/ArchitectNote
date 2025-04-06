package lesson

import (
	"time"
)

func Lesson01() {
	go PrintSomething("Hello")
	time.Sleep(1 * time.Second)
	PrintSomething("word")
}
