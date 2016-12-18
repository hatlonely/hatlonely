#!/usr/bin/env bash

function Build() {
    go build src/main/hellowords.go
}

function Clean() {
    rm -rf output hellowords
}

function Pack() {
    mkdir -p output
    mkdir -p output/data
    mkdir -p output/bin
    Build && mv hellowords output/bin && cp data/one.txt output/data/one.txt
}

function Help() {
    echo "sh build.sh [pack | clean | build]"
}

function Main() {
    case $1 in
        "pack") Pack;;
        "clean") Clean;;
        "build") Build;;
        *) Help;;
    esac
}

Main $@