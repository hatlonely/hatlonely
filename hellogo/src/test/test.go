package test

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

func Test() {
	s := []int{}
	for i := 0; i < 100000000; i++ {
		s = append(s, rand.Int())
	}
	t1 := time.Now()
	sort.Ints(s)
	t2 := time.Now()
	fmt.Println(t2.Sub(t1))
}

func Main() {
	Test()
}
