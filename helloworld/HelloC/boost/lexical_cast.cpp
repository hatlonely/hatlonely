//
//  lexical_cast.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  boost字符串和任意类型的相互转换的万能函数，性能一般，可读性好
//

#include <iostream>
#include <chrono>
#include <string>
#include <boost/lexical_cast.hpp>

namespace boost_lexical_cast {

std::string to_string(uint64_t number) {
    int len = 0;
    char buffer[32];
    
    uint64_t n = number;
    while (n > 0) {
        n /= 10;
        len++;
    }
    
    buffer[len] = '\0';
    while (number > 0) {
        buffer[--len] = '0' + (number % 10);
        number /= 10;
    }
    
    return std::string(buffer);
}

void benchmark() {
    auto start1 = std::chrono::system_clock::now();
    for (int i = 0; i < 100000; i++) {
        boost::lexical_cast<std::string>(1234567890123456789UL);
    }
    auto end1 = std::chrono::system_clock::now();
    std::cout << "lexical_cast time cost: " << (end1 - start1).count() << std::endl;
    
    auto start2 = std::chrono::system_clock::now();
    for (int i = 0; i < 100000; i++) {
        std::string str = to_string(1234567890123456789);
    }
    auto end2 = std::chrono::system_clock::now();
    std::cout << "mytostring time cost: " << (end2 - start2).count() << std::endl;
    
    auto start3 = std::chrono::system_clock::now();
    for (int i = 0; i < 100000; i++) {
        std::string str = std::to_string(1234567890123456789);
    }
    auto end3 = std::chrono::system_clock::now();
    std::cout << "std::to_string time cost: " << (end3 - start3).count() << std::endl;
}

void usage() {
    try {
        std::string str1 = boost::lexical_cast<std::string>(12345678901234567890UL);
        std::string str2 = boost::lexical_cast<std::string>(1234.5678);
        double d         = boost::lexical_cast<double>("1234.5678");
        uint64_t i       = boost::lexical_cast<uint64_t>("12345678901234567890");
        
        (void)i; (void)d;   // ignore unused warning
    } catch (boost::bad_lexical_cast &e) {
        std::cout << e.what() << std::endl;
    }
}

int main(int argc, const char* argv[]) {
    benchmark();
    usage();
    return 0;
}
    
}

