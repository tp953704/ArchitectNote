package lesson

import (
	"fmt"
	"sync"
)

var msgA string
var wg sync.WaitGroup

func updateMsg04(s string) {
	defer wg.Done()

	msgA = s
}

func Lesson4() {
	msgA = "hello world"
	wg.Add(2)
	go updateMsg04("hello")
	go updateMsg04("hello2")
	wg.Wait()
	fmt.Println(msgA)
}

// var msgA string
// var wg sync.WaitGroup

// func updateMsg04(s string, m *sync.Mutex) {
// 	defer wg.Done()
// 	m.Lock()
// 	msgA = s
// 	m.Unlock()
// }

// func Lesson4() {
// 	msgA = "hello world"
// 	var mutex sync.Mutex
// 	wg.Add(2)
// 	go updateMsg04("hello", &mutex)
// 	go updateMsg04("hello2", &mutex)
// 	wg.Wait()
// 	fmt.Println(msgA)
// }
