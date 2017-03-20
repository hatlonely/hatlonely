#!/usr/bin/env bash

function main() {
    export GOPATH=`pwd`
    go get github.com/Workiva/go-datastructures/...
    go get github.com/paked/configure
}

main