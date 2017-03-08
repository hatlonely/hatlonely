package buildin

import (
	"fmt"
	"strings"
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
}

func Main() {
	Strings()
	Array()
	Slice()
}
