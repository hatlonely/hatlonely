//
//  thread.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/23.
//  Copyright © 2015年 hatlonely. All rights reserved.
//

#include <iostream>
#include <thread>

namespace c11_thread {

// thread
void thread_func_with_no_param() {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::cout << "thread_func_with_no_param" << std::endl;
}

void thread_func_with_param(int a, int b, int& result) {
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    result = a + b;
    std::cout << "thread_func_with_param: " << a << " + " << b << " = " << result << std::endl;
}

struct thread_func_struct {
    void operator()(int a, int b, int& result) {
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        result = a * b;
        std::cout << "thread_func_struct: " << a << " * " << b << " = " << result << std::endl;
    }
};

void thread_usage() {
    int a = 1, b = 2, result1, result2;
    
    std::thread thread1(thread_func_with_no_param);
    std::thread thread2(thread_func_with_param, a, b, std::ref(result1));
    std::thread thread3(thread_func_struct(), a, b, std::ref(result2));
    
    thread1.join();
    thread2.join();
    thread3.join();
    // thread1.detach();
    // thread2.detach();
    // thread3.detach();
    
    std::cout << "result1: " << result1 << std::endl;
    std::cout << "result2: " << result2 << std::endl;
}

// mutex
void thread_func1(std::mutex& m) {
    for (int i = 0; i < 10; i++) {
        m.lock();       // 加锁
        std::cout << "thread1 " << i << std::endl;
        m.unlock();     // 解锁
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void thread_func2(std::mutex& m) {
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // lock_guard在构造后加锁，在作用域解释后自动释放锁
        std::lock_guard<std::mutex> lg(m);
        std::cout << "thread2 " << i << std::endl;
    }
}

void mutex_usage() {
    std::mutex m;
    
    std::thread thread1(thread_func1, std::ref(m));
    std::thread thread2(thread_func2, std::ref(m));
    
    thread1.join();
    thread2.join();
}

}

// condition_variable
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

namespace c11_thread {

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id (int id) {
    std::unique_lock<std::mutex> lck(mtx);
    // while (!ready) cv.wait(lck);
    cv.wait(lck, []{return ready;});
    std::cout << "thread " << id << '\n';
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

void condition_variable_usage() {
    std::thread threads[10];
    // spawn 10 threads:
    for (int i=0; i<10; ++i) {
        threads[i] = std::thread(print_id, i);
    }
    
    std::cout << "10 threads ready to race...\n";
    go();
    
    for (auto& th : threads) {
        th.join();
    }
}

}

#include <atomic>

namespace c11_thread {

void atomic_usage() {
    std::atomic<int> ai(5);
    ai++;
    ai += 100;
    
    std::cout << ai << std::endl;
}

int main(int argc, const char *argv[]) {
    thread_usage();
    mutex_usage();
    condition_variable_usage();
    atomic_usage();
    
    return 0;
}
    
}
