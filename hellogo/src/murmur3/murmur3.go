package murmur3

import (
	"fmt"
	"github.com/spaolacci/murmur3"
)

func MurMur3() {
	fmt.Println(murmur3.Sum64([]byte("hello world")))
	fmt.Println(murmur3.Sum64([]byte("foo")))
}

func Main() {
	MurMur3()
}
