package buildin

import (
	"bufio"
	"container/list"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"math"
	"math/rand"
	"net/url"
	"os"
	"path"
	"path/filepath"
	"sort"
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
	{
		str := "0123456789"
		str = str[:4] + str[5:]
		fmt.Println(str)
		fmt.Println(str[5:9])
		fmt.Println(str[0:4])
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

	{
		s := []int{1, 2, 3}
		func(s []int) {
			s = append(s, 4)
		}(s)
		fmt.Println(s)
		func(s *[]int) {
			*s = append(*s, 4)
		}(&s)
		fmt.Println(s)
	}

	{
		s := func() *[]int {
			return &[]int{1, 2, 3}
		}()
		fmt.Println(s)
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

	fmt.Println(time.Unix(unixtimenano/1000000000, unixtimenano%1000000000))

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

func Json() {
	bytes := []byte(`{"name": "hatlonely", "skill": ["c++", "java", "python", "go"], "desc": "配置中心"}`)
	var jsonobj map[string]interface{}
	json.Unmarshal(bytes, &jsonobj)
	fmt.Println(jsonobj)
	fmt.Println(jsonobj["name"])
	fmt.Println(jsonobj["skill"].([]interface{})[1])
	for _, v := range jsonobj["skill"].([]interface{}) {
		fmt.Println(v.(string))
	}

	str1, _ := json.Marshal(jsonobj)
	str2, _ := json.MarshalIndent(jsonobj, "", "\t")
	fmt.Println(string(str1))
	fmt.Println(string(str2))
}

func Os() {
	fmt.Println(os.Getpid())
	fmt.Println(os.Getppid())
	fmt.Println(os.Getuid())
	fmt.Println(os.Getwd())
	fmt.Println(os.Getenv("HOME"))

	// 遍历一个目录
	fileInfos, _ := ioutil.ReadDir("src/main")
	for _, fileInfo := range fileInfos {
		fmt.Println(fileInfo.Name())
	}
	fmt.Println(path.Join("src/", "main", "helloworld.go"))

	fmt.Println(filepath.Base("src/main/helloworld.go"))
	fmt.Println(filepath.Dir("src/main/helloworld.go"))
	fmt.Println(filepath.Dir("src/main/"))
	fmt.Println(filepath.Dir("src/main"))
}

func Url() {
	u, _ := url.Parse("https://www.google.com/?q=hello+world")
	fmt.Println(u.Scheme)
	fmt.Println(u.Host)
	fmt.Println(u.Query())
	v := u.Query()
	v.Set("q", "hello go")
	u.RawQuery = v.Encode()
	fmt.Println(u)
}

func Bufio() {
	{
		file, _ := os.Open("src/main/main.go")
		defer file.Close()
		scanner := bufio.NewScanner(bufio.NewReader(file))
		for scanner.Scan() {
			fmt.Println(scanner.Text())
		}
		if err := scanner.Err(); err != nil {
			fmt.Println(err)
		}
	}
	{
		file, _ := os.Open("src/main/main.go")
		defer file.Close()
		reader := bufio.NewReader(file)
		for {
			line, err := reader.ReadBytes('\n')
			if err != nil {
				break
			}
			fmt.Println(string(line))
		}
	}
	{
		file, _ := os.Open("src/main/main.go")
		defer file.Close()
		bytes, _ := ioutil.ReadAll(file)
		fmt.Println(string(bytes))
	}
	{
		bytes, _ := ioutil.ReadFile("src/main/main.go")
		fmt.Println(string(bytes))
	}
}

func Sort() {
	ia := []int{4, 3, 2, 1}
	sort.Ints(ia)
	fmt.Println(ia)
}

func Search() {
	fmt.Println(sort.SearchInts([]int{1, 4, 7, 8}, 7)) // 2
	fmt.Println(sort.SearchInts([]int{1, 4, 7, 8}, 6)) // 2
}

func Channel() {
	c1 := make(chan int, 5)
	c2 := make(chan int, 5)
	go func() {
		for i := 0; i < 10; i++ {
			c1 <- i
			c2 <- 100 + i
			time.Sleep(time.Duration(1) * time.Second)
		}
	}()

OuterLoop:
	for {
		select {
		case i := <-c1:
			fmt.Println(i)
		case i := <-c2:
			fmt.Println(i)
		case <-time.Tick(time.Duration(2) * time.Second):
			fmt.Println("timeout")
			break OuterLoop
		}
	}
}

func Switch() {
	astr := "a"
	switch astr {
	case "a":
		fmt.Println("a")
	case "b":
		fmt.Println("b")
	}
}

func Random() {
	for j := 0; j < 10; j++ {
		rand.Seed(1234567)
		l := []int{}
		for i := 0; i < 9; i++ {
			l = append(l, rand.Intn(100))
		}
		sort.Ints(l)
		fmt.Println(l)
	}
}

func Defer() {
	now := time.Now()
	defer fmt.Println(time.Since(now))
	defer func() { fmt.Println(time.Since(now)) }()

	for i := 0; i < 10; i++ {
		fmt.Println("abc")
	}
	time.Sleep(2 * time.Second)
	fmt.Println(time.Since(now))
}

func Main() {
	Strings()
	Array()
	Slice()
	Dict()
	ContainerList()
	Time()
	Math()
	Json()
	Os()
	Url()
	Bufio()
	Sort()
	Search()
	Channel()
	Switch()
	Random()
	Defer()
}
