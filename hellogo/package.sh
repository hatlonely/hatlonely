#!/usr/bin/env bash

export GOPATH=`pwd`

function main() {
    go get -u -v github.com/Workiva/go-datastructures/...
    go get -u -v github.com/paked/configure
}

main
