//
//  container.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <vector>
#include <array>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>

namespace c11_container {

// std::vector
// size()   记录了当前元素的个数
// capacity()   不重新分配内存的话，可以保存多少个元素
// reserve(n)   分配至少能容纳n个元素的内存空间
// shrink_to_fit()  将capacity减少为于size()相同的大小
void vector_usage() {
    std::vector<int> vi;
    assert(vi.size() == 0);
    assert(vi.capacity() == 0);
    vi.reserve(1024);
    assert(vi.size() == 0);
    assert(vi.capacity() == 1024);
    
    std::vector<std::string> vs(5);
    assert(vs.size() == 5);
    assert(vs.capacity() == 5);
    vs.push_back("sissie");
    assert(vs[5] == "sissie");
    assert(vs.size() == 6);
    assert(vs.capacity() == 10);
    vs.shrink_to_fit();
    assert(vs.capacity() == 6);
}

// std::array
// C++11新增的容器，固定大小的数组，支持快速随机访问，不能添加或删除元素
void array_usage() {
    std::array<std::string, 5> as0;
    std::array<int, 5> ai1{ {1, 2, 3, 4, 5} };
    std::array<std::string, 5> as2 = { {"sissie", "playjokes", "hatlonely", "robin", "sky"} };
    assert(ai1[0] == 1);
    assert(as2[0] == "sissie");
}

// std::forward_list
// 单向列表，只支持单向顺序遍历
void forward_list_usage() {
    std::forward_list<std::string> fls{ {"sissie", "playjokes", "hatlonely", "robin", "sky"} };
    for (const auto& name: fls) {
        std::cout << name << std::endl;
    }
}

// std::unordered_set
// std::unordered_multiset
// std::unordered_map
// std::unordered_multimap
// 无序的集合，用hash实现，容器内的元素必须要由对应的hash函数
// 基本类型的hash都已经由标准库实现
void unordered_usage() {
    std::unordered_set<int> usi = { {11, 22, 33, 44, 55, 66, 77, 88, 99, 0} };
    assert(usi.size() == 10);
    usi.insert(66);
    assert(usi.size() == 10);
    
    // 0,99,88,77,66,55,44,33,22,11,
    for (const auto& i: usi) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
    // 0,11,22,33,44,55,66,77,88,99,
    std::set<int> si = { {11, 22, 33, 44, 55, 66, 77, 88, 99, 0} };
    for (const auto& i: si) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
    
    std::unordered_multiset<int> umsi = { {11, 22, 33, 44, 55, 66, 77, 88, 99, 0} };
    assert(umsi.size() == 10);
    assert(umsi.count(66) == 1);
    umsi.insert(66);
    assert(umsi.size() == 11);
    assert(umsi.count(66) == 2);
    
    std::unordered_map<std::string, double> book_price_map{ {
        {"C++ Primer", 128.00},
        {"UNIX 环境高级编程", 99.00},
        {"HBase 权威指南", 89.00},
        {"MapReduce 设计模式", 49.00}
    } };
    for (const auto& book_price_pair: book_price_map) {
        std::cout << book_price_pair.first << " => " << book_price_pair.second << std::endl;
    }
}
    
void ordered_usage() {
    std::set<int> si = {3, 7, 1, 2, 4, 8, 5, 9};
    std::cout << *si.lower_bound(6) << std::endl;   // 7
    std::cout << *si.upper_bound(6) << std::endl;   // 7
    std::cout << *si.lower_bound(5) << std::endl;   // 5
    std::cout << *si.upper_bound(5) << std::endl;   // 7
}

int main(int argc, const char *argv[]) {
    vector_usage();
    array_usage();
    forward_list_usage();
    unordered_usage();
    ordered_usage();
    
    return 0;
}

}
