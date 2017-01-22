#!/usr/bin/env bash

kWorkRoot=".."

alias thrift="$kWorkRoot/third/thrift-0.10.0/bin/thrift"

function Warn() {
    echo "[31m$1[0m"
}

function Info() {
    echo "[32m$1[0m"
}

function GenCppCode() {
    mkdir -p cpp
    thriftFile=$1
    thrift -r -gen cpp -out cpp $thriftFile && rm -rf cpp/*skeleton.cpp &&
    Info "GenCppCode $thriftFile success" && return 0
    Warn "GenCppCode $thriftFile failed" && return 255
}

function GenPhpCode() {
    mkdir -p php
    thriftFile=$1
    thrift -r -gen php -out php $thriftFile &&
    Info "GenPhpCode $thriftFile success" && return 0
    Warn "GenPhpCode $thriftFile failed" && return 255
}

function GenPyCode() {
    mkdir -p py
    thriftFile=$1
    thrift -r -gen py -out ../tools/py $thriftFile &&
    Info "GenPyCode $thriftFile success" && return 0
    Warn "GenPyCode $thriftFile failed" && return 255
}

function GenCode() {
    thriftFile=$1
    GenCppCode $thriftFile && GenPhpCode $thriftFile && GenPyCode $thriftFile && return 0
    return 255
}

function Main() {
    GenCode leveldb_cpp_thrift.thrift
}

Main

