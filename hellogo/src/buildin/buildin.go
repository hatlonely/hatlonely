package buildin

import (
	"container/list"
	"fmt"
	"math"
	"math/rand"
	"strings"
	"time"
)

func Strings() {
	{
		hello := "hello"
		world := "world"
		fmt.Printf("%s %s\n", hello, world)
		helloworld := fmt.Sprintf("%s %s\n", hello, world)
		fmt.Println(helloworld)
	}
	{
		text := "to be or not to be that is a question"
		if strings.Contains(text, "question") {
			fmt.Printf("[%s] contains [%s]\n", text, "question")
		}
		if strings.ContainsAny(text, " \n\t") {
			fmt.Printf("[%s] contains space\n", text)
		}
		if strings.HasPrefix(text, "to be") {
			fmt.Printf("[%s] has prefix [%s]\n", text, "to be")
		}
		fmt.Println(strings.Count(text, "to"))
		fmt.Println(strings.Index(text, "be"))
		fmt.Println(strings.Split(text, " "))
		fmt.Println(strings.Join(strings.Split(text, " "), ", "))
		fmt.Println(strings.Trim(text, " ton"))
		fmt.Println(strings.Replace(text, " ", ", ", 1))
	}
}

func Array() {
	ia := [...]int{0, 1, 2, 3, 4, 5}
	fmt.Println(ia)
	is := ia[1:3]
	fmt.Println(is)
	ia[2] = 22
	fmt.Println(ia)
}

func Slice() {
	is := []int{}
	for i := 0; i < 5; i++ {
		is = append(is, i)
	}
	fmt.Println("len(is): ", len(is))
	fmt.Println("cap(is): ", cap(is))
	fmt.Println(is)
	is = is[1:] // 删除第一个
	fmt.Println(is)
	is = is[:len(is)-1] // 删除最后一个
	fmt.Println(is)
	is = append(is[:1], is[2:]...) // 删除is[1]
	fmt.Println(is)
	is[1] = 33 // 修改
	fmt.Println(is)

	// 遍历
	for idx, val := range is {
		fmt.Println(idx, " => ", val)
	}
}

func Dict() {
	{
		dict := map[string]int{
			"zero":  0,
			"one":   1,
			"two":   2,
			"three": 33,
		}
		dict["three"] = 3    // 修改key
		dict["four"] = 4     // 增加key
		delete(dict, "zero") // 删除key
		fmt.Println(dict)

		// 遍历
		for key, val := range dict {
			fmt.Println(key, " => ", val)
		}
	}
}

func ContainerList() {
	l := list.New()
	l.PushBack("hatlonely") // 从链表后面插入
	l.PushBack(25)
	l.PushBack("hatlonely@gmail.com")
	l.PushBack(127.9)
	l.InsertAfter("hello world", l.Back().Prev()) // 从元素后面插入
	l.InsertBefore("list", l.Front())             // 从元素前面插入

	l.Remove(l.Front()) // 删除

	fmt.Println(l.Len())

	// 顺序遍历
	for e := l.Front(); e != nil; e = e.Next() {
		fmt.Print(e.Value, ", ")
	}
	fmt.Println()
	// 逆序便利
	for e := l.Back(); e != nil; e = e.Prev() {
		fmt.Print(e.Value, ",")
	}
	fmt.Println()
}

func Time() {
	t1 := time.Now()
	fmt.Println(t1)

	unixtime := time.Now().Unix()
	fmt.Println(unixtime)

	unixtimenano := time.Now().UnixNano()
	fmt.Println(unixtimenano)

	yyyymmddhhmmss := time.Now().Format("2006-01-02 15:04:05")
	rfc3399time := time.Now().Format(time.RFC3339)
	fmt.Println(yyyymmddhhmmss, rfc3399time)

	delta1, _ := time.ParseDuration("24h")
	delta2, _ := time.ParseDuration("-24h")
	t2 := t1.Add(delta1)
	t3 := t1.Add(delta2)
	delta3 := t1.Sub(t2)
	fmt.Println(t2, t3, delta3, delta1+delta2)
}

func Math() {
	{
		rand.Seed(time.Now().Unix())
		r1 := rand.Int()
		r2 := rand.Intn(100)
		f1 := rand.Float64()
		f2 := rand.NormFloat64()
		f3 := rand.ExpFloat64()
		fmt.Println(r1, r2, f1, f2, f3)
	}
	{
		f1 := math.Sin(math.Pi / 3)
		f2 := math.Cos(math.Pi / 3)
		fmt.Println(f1, f2)
	}
}

func Main() {
	Strings()
	Array()
	Slice()
	Dict()
	ContainerList()
	Time()
	Math()
}
