#!/usr/bin/env bash

kWorkRoot=$(pwd)

function Warn() {
    echo "[31m$1[0m"
}

function Info() {
    echo "[32m$1[0m"
}

function InstallLeveldb() {
    output="leveldb-v1.19"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget https://github.com/google/leveldb/archive/v1.19.zip -O $output.zip &&
    unzip $output.zip && cd leveldb-1.19 &&
    make -j8 && mkdir output && mkdir -p output/lib &&
    cp -r include output/ && cp out-static/*.a output/lib/ &&
    mv output/* $kWorkRoot/$output &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallLibevent() {
    output="libevent-2.0.22"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget https://github.com/libevent/libevent/releases/download/release-2.0.22-stable/libevent-2.0.22-stable.tar.gz -O $output.tar.gz &&
    tar -xzvf $output.tar.gz && cd libevent-2.0.22-stable &&
    ./configure --prefix=$kWorkRoot/$output && make -j8 && make install && rm -rf output/lib/*.dylib &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallBison() {
    output="bison-2.5"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget http://ftp.gnu.org/gnu/bison/bison-2.5.tar.gz -O $output.tar.gz &&
    tar -xzvf $output.tar.gz && cd bison-2.5 &&
    ./configure --prefix=$kWorkRoot/$output && make -j8 && make install &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallThrift() {
    export PATH=$kWorkRoot/bison-2.5/bin:$PATH
    output="thrift-0.10.0"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget http://mirrors.cnnic.cn/apache/thrift/0.10.0/thrift-0.10.0.tar.gz -O $output.tar.gz &&
    tar -xzvf $output.tar.gz && cd thrift-0.10.0 &&
    ./configure CXXFLAGS='-g -O2' --enable-shared=no --with-nodejs=no --prefix=$kWorkRoot/$output && make -j8 && make install &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallLibconfig() {
    output="libconfig-1.5"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget http://www.hyperrealm.com/libconfig/libconfig-1.5.tar.gz &&
    tar -xzvf libconfig-1.5.tar.gz && cd libconfig-1.5 &&
    ./configure --prefix=$kWorkRoot/$output &&
    make && make install &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallLog4cplus() {
    output="log4cplus-1.2.0"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget http://nchc.dl.sourceforge.net/project/log4cplus/log4cplus-stable/1.2.0/log4cplus-1.2.0.tar.xz &&
    tar -xvf log4cplus-1.2.0.tar.xz && cd log4cplus-1.2.0 &&
    ./configure --prefix=$kWorkRoot/$output &&
    make && make install &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallGtest() {
    output="gtest-1.8.0"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p gtest-1.8.0/src && cd gtest-1.8.0/src &&
    wget https://codeload.github.com/google/googletest/zip/release-1.8.0 -O release-1.8.0.zip &&
    unzip release-1.8.0.zip && cd googletest-release-1.8.0 &&
    mkdir build && cd build && cmake .. -DCMAKE_INSTALL_PREFIX=$kWorkRoot/$output &&
    make && make install &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallGflags() {
    output="gflags-v2.2.0"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget https://codeload.github.com/gflags/gflags/tar.gz/v2.2.0 -O $output.tar.gz &&
    tar -xzvf $output.tar.gz && cd gflags-2.2.0 &&
    mkdir cbuild && cd cbuild && cmake .. -DCMAKE_INSTALL_PREFIX=$kWorkRoot/$output && make && make install &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallBoost() {
    output="boost_1_63_0"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget https://nchc.dl.sourceforge.net/project/boost/boost/1.63.0/boost_1_63_0.tar.gz &&
    tar -xzvf boost_1_63_0.tar.gz && cd boost_1_63_0 &&
    ./bootstrap.sh && ./b2 install --prefix=$kWorkRoot/$output &&
    Info "install $output succ" && return 0
    Warn "install $output fail" && return 255
}

function InstallSnappy() {
    output="snappy-1.1.3"
    [[ -e $output ]] && Info "$output is exists" && return 0
    mkdir -p $output/src && cd $output/src &&
    wget https://codeload.github.com/google/snappy/zip/1.1.3 -O $output.zip &&
    unzip $output.zip && cd snappy-1.1.3 &&
    return 0
}

function Main() {
    (InstallLeveldb)
    (InstallLibevent)
    (InstallBison)
    (InstallThrift)
    (InstallLibconfig)
    (InstallLog4cplus)
    (InstallGtest)
    (InstallGflags)
    (InstallBoost)
    (InstallSnappy)
}

Main
