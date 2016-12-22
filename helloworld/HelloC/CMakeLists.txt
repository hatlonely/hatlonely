CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(HELLOC)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -std=c++11")
SET(WORK_ROOT "../../../..")

AUX_SOURCE_DIRECTORY(glog glog)
AUX_SOURCE_DIRECTORY(libconfig libconfig)
AUX_SOURCE_DIRECTORY(boost boost)
AUX_SOURCE_DIRECTORY(hiredis hiredis)
AUX_SOURCE_DIRECTORY(log4cplus log4cplus)
AUX_SOURCE_DIRECTORY(mysql mysql)
AUX_SOURCE_DIRECTORY("c++11" "c++11")
SET(SOURCES main.cpp ${glog} ${libconfig} ${boost} ${hiredis} ${log4cplus} ${mysql} ${c++11})

INCLUDE_DIRECTORIES(
    "./include"
    "/usr/local/include"
    "/usr/local/mysql/include"
)

LINK_DIRECTORIES(
    "/usr/local/lib"
    "/usr/local/mysql/lib"
)

ADD_DEFINITIONS(
)

ADD_EXECUTABLE(helloc ${SOURCES})

TARGET_LINK_LIBRARIES(
    helloc
    glog
    config++
    boost_system
    boost_date_time
    boost_regex
    gmp
    log4cplus
    mysqlclient
    hiredis
)

ADD_CUSTOM_COMMAND(
    TARGET helloc
    POST_BUILD
    COMMAND echo "${HELLOC_SOURCE_DIR}"
    COMMAND echo "${HELLOC_BINARY_DIR}"
)
