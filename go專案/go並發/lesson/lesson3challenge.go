package lesson

import (
	"fmt"
	"sync"
)

var msg string

func updateMessage(s string) {
	msg = s
}

func printMessage() {
	fmt.Println(msg)
}

func Lesson03() {
	var wg sync.WaitGroup
	// challenge: modify this code so that the calls to updateMessage() on lines
	// 28, 30, and 33 run as goroutines, and implement wait groups so that
	// the program runs properly, and prints out three different messages.
	// Then, write a test for all three functions in this program: updateMessage(),
	// printMessage(), and main().
	wg.Add(1)
	msg = "Hello, world!"
	go func() {
		updateMessage("Hello, universe!")
		printMessage()
		wg.Done()
	}()
	wg.Wait()
	wg.Add(1)
	go func() {
		updateMessage("Hello, universe!")
		printMessage()
		wg.Done()
	}()
	wg.Wait()
	wg.Add(1)
	go func() {
		updateMessage("Hello, cosmos!")
		printMessage()
		wg.Done()
	}()
	wg.Wait()
	wg.Add(1)
	go func() {
		updateMessage("Hello, world!")
		printMessage()
		wg.Done()
	}()
	wg.Wait()
}
