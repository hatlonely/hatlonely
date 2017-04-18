package main

import "hdb"

func main() {
	if err := hdb.Init(); err != nil {
		panic(err)
	}

	if err := hdb.Run(); err != nil {
		panic(err)
	}
}
