//
//  semantics.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <vector>
#include <map>

namespace c11_semantics {

void print_initializer_list(std::initializer_list<int> il) {
    for (auto i: il) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

std::vector<std::string> my_array() {
    return {"sissie", "robin", "playjokes", "sky", "hatlonely"};
}

//  容器初始化
void initialization_usage() {
    std::vector<int> vi = {1, 2, 3, 4, 5};
    std::map<int, std::string> mis = {
        {1, "c"},
        {2, "java"},
        {3, "c++"}
    };
    
    std::vector<std::string> vs{{"sissie", "robin", "playjokes", "sky", "hatlonely"}};
    
    print_initializer_list({1, 2, 3, 4, 5, 6});
    std::vector<std::string> vs2 = my_array();
}

// 关键字auto
void auto_usage() {
    auto i = 0;
    auto str = "sissie";
    assert(typeid(i) == typeid(int));
    assert(typeid(str) == typeid(const char *));
}

// for循环
void for_usage() {
    std::map<int, std::string> mis = {
        {1, "c"},
        {2, "java"},
        {3, "c++"}
    };
    
    for (auto it = mis.begin(); it != mis.end(); ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }
    
    for (const auto& kv : mis) {
        std::cout << kv.first << " => " << kv.second << std::endl;
    }
}

// lambda表达式
// []内的参数指的是Lambda表达式可以取得的全局变量
// 如果在[]中传入=的话，即是可以取得所有的外部变量
// ()内的参数是每次调用函数时传入的参数
// ->后加上的是Lambda表达式返回值的类型
void lambda_usage() {
    std::vector<int> vi = {1, 2, 3, 4, 5};
    int a = 5, b = 6;
    for_each(vi.begin(), vi.end(), [a](int& x) {
        std::cout << x * a << std::endl;
    });
    
    for_each(vi.begin(), vi.end(), [=](int &x) {
        x *= (a + b);
    });
    
    for_each(vi.begin(), vi.end(), [a](int& x) {
        std::cout << x << std::endl;
    });
    
    for_each(vi.begin(), vi.end(), [=](int &x)->int {
        return x * (a + b);
    });
    
    size_t i = 42;
    auto f = [i]() mutable {
        return ++i;
    };
    i = 0;
    std::cout << f();   // 43
    std::cout << f();   // 44
    std::cout << std::endl;
}
    
// 可变参数模板
template <typename T>
int sum(T t) {
    return t;
}
template <typename T, typename ...Args>
int sum(T t, Args ...args) {
    return t + sum(args...);
}
    
int sum(std::initializer_list<int> li) {
    int total = 0;
    for (auto i : li) {
        total += i;
    }
    return total;
}

void parameter_pack() {
    std::cout << sum(1, 2, 3) << std::endl;
    std::cout << sum(1, 2, 3, 4) << std::endl;
    std::cout << sum({1, 2, 3}) << std::endl;
    std::cout << sum({1, 2, 3, 4}) << std::endl;
}

int main(int argc, const char *argv[]) {
    initialization_usage();
    auto_usage();
    for_usage();
    lambda_usage();
    parameter_pack();
    return 0;
}

}