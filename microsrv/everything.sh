#!/usr/bin/env bash

WORK_ROOT=`pwd`
export GOPATH=${WORK_ROOT}

function warn() {
    echo "[31m$1[0m"
}

function info() {
    echo "[32m$1[0m"
}

function install_protoc() {
    output=${WORK_ROOT}/third/protobuf-3.2.0
    [[ -e ${output} ]] && info "${output} is exists" && return 0
    mkdir -p third && cd third &&
    wget https://github.com/google/protobuf/releases/download/v3.2.0/protobuf-cpp-3.2.0.tar.gz &&
    tar -xzvf protobuf-cpp-3.2.0.tar.gz && cd protobuf-3.2.0 &&
    ./configure --prefix=${output} && make -j8 && make install &&
    info "install protoc success" && return 0
    warn "install protoc fail" && return 255
}

function install_go_dependency() {
    go get -v -u github.com/golang/protobuf/proto github.com/golang/protobuf/protoc-gen-go &&
    go get -v -u google.golang.org/grpc &&
    go get -v -u github.com/cihub/seelog &&
    go get -v -u github.com/spf13/viper &&
    go get -v -u github.com/satori/go.uuid &&
    go get -v -u github.com/gsdocker/gsos/uuid &&
    go get -v -u github.com/syndtr/goleveldb/leveldb &&
    go get -v -u github.com/spaolacci/murmur3 &&
    info "install go dependency success" && return 0
    warn "install go dependency fail" && return 255
}

function build() {
    mkdir -p output/
    for f in $(\ls src/main); do
        go build src/main/${f}
        if [[ $? != 0 ]]; then
            warn "build src/main/${f} failed." && return 255
        fi
    done
    mv vta_server output/
    mv vta_client output/
    info "build success" && return 0
}

function unit() {
    for f in $(\ls src/*/*_test.go); do
        go test -v ${f} ${f%_test.go}.go
        if [[ $? != 0 ]]; then
            warn "unit test ${f} failed." && return 255
        fi
    done
    info "unit success" && return 0
}

function usage() {
    info "usage: "
    info "  sh everything.sh <dependency | unit | build>"
    info "  dependency  安装依赖"
    info "  codegen     生成代码"
    info "  unit        单元测试"
    info "  build       编译"
}

function main() {
    case $1 in
        "dependency") install_protoc && install_go_dependency;;
        "codegen") codegen;;
        "unit") unit;;
        "build") build;;
        *) usage;;
    esac
}

main $1

