CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(LEVELDB_CPP_THRIFT)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(TAG_VERSION "1_0_0_0")
SET(WORK_ROOT ".")
IF(debug)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -g")
    ADD_DEFINITIONS(
        -DDEBUG=1
    )
ELSE()
    SET(CMAKE_CXX_FLAGS "-std=c++11 -O2")
ENDIF()
IF(gprof)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -pg")
ENDIF()

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(protocols/cpp PROTOCOLS)

INCLUDE_DIRECTORIES(
    "include"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/protocols/cpp/"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/leveldb-v1.19/include"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/thrift-0.10.0/include"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/gflags-v2.2.0/include"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/libconfig-1.5/include"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/log4cplus-1.2.0/include"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/boost_1_63_0/include"
)

LINK_DIRECTORIES(
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/leveldb-v1.19/lib"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/thrift-0.10.0/lib"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/gflags-v2.2.0/lib"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/libconfig-1.5/lib"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/log4cplus-1.2.0/lib"
    "${LEVELDB_CPP_THRIFT_SOURCE_DIR}/${WORK_ROOT}/third/boost_1_63_0/lib"
)

ADD_DEFINITIONS(
    -DTAG_VERSION="${TAG_VERSION}"
)

ADD_EXECUTABLE(leveldb_cpp_thrift ${SOURCES} ${PROTOCOLS})

TARGET_LINK_LIBRARIES(
    leveldb_cpp_thrift
    thrift
    gflags
    config++
    log4cplus
    leveldb
    snappy
)

ADD_CUSTOM_COMMAND(
    TARGET leveldb_cpp_thrift
    POST_BUILD
    COMMAND cp -r ${LEVELDB_CPP_THRIFT_SOURCE_DIR}/conf/ ${LEVELDB_CPP_THRIFT_BINARY_DIR}/conf/
)
