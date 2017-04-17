#!/usr/bin/env bash

WORK_ROOT=`pwd`
export GOPATH=${WORK_ROOT}

function warn() {
    echo "[31m$1[0m"
}

function info() {
    echo "[32m$1[0m"
}

function install_go_dependency() {
    go get -v -u github.com/emirpasic/gods
    go get -v -u github.com/Workiva/go-datastructures/... &&
    go get -v -u github.com/paked/configure &&
    go get -v -u github.com/spaolacci/murmur3 &&
    info "install go dependency success" && return 0
    warn "install go dependency fail" && return 255
}

function build() {
    for f in $(\ls src/main); do
        go build src/main/${f}
        if [[ $? != 0 ]]; then
            warn "build src/main/${f} failed." && return 255
        fi
    done
    info "build success" && return 0
}

function unit() {
    dirs=""
    for dir in ${dirs}; do
        go test -v src/${dir}/*.go
        if [[ $? != 0 ]]; then
            warn "unit test src/${dir} failed." && return 255
        fi
    done
    info "unit success" && return 0
}

function usage() {
    info "usage: "
    info "  sh everything.sh <dependency | unit | build>"
    info "  dependency  安装依赖"
    info "  unit        单元测试"
    info "  build       编译"
}

function main() {
    case $1 in
        "dependency") install_go_dependency;;
        "unit") unit;;
        "build") build;;
        *) usage;;
    esac
}

main $@

