#!/usr/bin/env bash

export GOPATH=`pwd`

function main() {
    go get -v -u github.com/Workiva/go-datastructures/...
    go get -v -u github.com/paked/configure
    go get -v -u github.com/spaolacci/murmur3
    go get github.com/emirpasic/gods
}

main
