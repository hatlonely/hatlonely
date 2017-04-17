package gods

import (
	"fmt"
	"github.com/emirpasic/gods/lists/singlylinkedlist"
	"github.com/emirpasic/gods/maps/treebidimap"
	"github.com/emirpasic/gods/maps/treemap"
	"github.com/emirpasic/gods/utils"
)

func List() {
	li := singlylinkedlist.New()
	li.Add("a")
	li.Add("b")
	fmt.Println(li.Get(0))
	li.Remove(0)
	fmt.Println(li.Get(0))
}

func TreeMap() {
	m := treemap.NewWithIntComparator()
	m.Put(2, "two")
	m.Put(1, "one")
	m.Put(4, "four")
	m.Put(5, "five")
	m.Put(3, "three")

	for i := 0; i < 5; i++ {
		k, v := m.Min()
		fmt.Println(k, v)
		m.Remove(k)
	}
}

func TreeBidiMap() {
	m := treebidimap.NewWith(utils.IntComparator, utils.StringComparator)
	m.Put(2, "two")
	m.Put(1, "one")
	m.Put(4, "four")
	m.Put(5, "five")
	m.Put(3, "three")

	fmt.Println(m.Get(1))
	fmt.Println(m.GetKey("one"))

	it := m.Iterator()
	for it.Next() {
		fmt.Println(it.Key(), it.Value())
	}

	{
		aa := m.Iterator()
		aa.Next()
		fmt.Println(aa.Key(), aa.Value())
	}
	{
		aa := m.Iterator()
		aa.Next()
		fmt.Println(aa.Key(), aa.Value())
		m.Remove(aa.Key())
	}
}

func Main() {
	List()
	TreeMap()
	TreeBidiMap()
}
