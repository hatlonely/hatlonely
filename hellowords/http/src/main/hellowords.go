package main

import (
    "io"
    "io/ioutil"
    "fmt"
    "strings"
    "net/http"
    "math/rand"
    "time"
)

var OneWords []string

func Init() error {
    rand.Seed(time.Now().Unix())
    lines, err := ioutil.ReadFile("data/one.txt")
    if err != nil {
        fmt.Println("open data/one.txt failed.")
        return err
    }
    
    OneWords = strings.Split(string(lines), "\n")

    return nil
}

func SayHello(response http.ResponseWriter, request *http.Request) {
    io.WriteString(response, OneWords[rand.Intn(len(OneWords))])
}

func main() {
    Init()

    http.HandleFunc("/", SayHello)
    err := http.ListenAndServe(":3000", nil)
    if err != nil {
        fmt.Println("http listen failed.")
    }
}
