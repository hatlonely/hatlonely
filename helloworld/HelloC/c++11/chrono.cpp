//
//  chrono.cpp
//  HelloC
//
//  Created by hatlonely on 16/2/9.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <thread>

namespace c11_chrono {
    
int main(int argc, const char *argv[]) {
        {
            auto start_ms = std::chrono::system_clock::now();
            auto start_us = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::nanoseconds(123456789));
            auto end_ms = std::chrono::system_clock::now();
            auto end_us = std::chrono::steady_clock::now();
            std::cout << (end_ms - start_ms).count() << std::endl;
            std::cout << (end_us - start_us).count() << std::endl;
        } {
            std::chrono::high_resolution_clock::time_point t1(std::chrono::nanoseconds(20));
            std::chrono::high_resolution_clock::time_point t2(std::chrono::nanoseconds(100));
            std::cout << (t2 - t1).count() << std::endl;
        } {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::this_thread::sleep_until(std::chrono::steady_clock::time_point(std::chrono::milliseconds(10)));
        }

    return 0;
}
    
}
