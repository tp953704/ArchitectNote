package lesson

import (
	"fmt"
	"sync"
)

func Lesson02() {
	var wg sync.WaitGroup

	words := []string{
		"a",
		"b",
		"c",
		"d",
	}
	wg.Add(len(words))
	// wg.Add(5)

	for i, w := range words {
		go func() {
			defer wg.Done()
			PrintSomething(fmt.Sprintf("%d:%s", i, w))
		}()
	}
	wg.Wait()
}
