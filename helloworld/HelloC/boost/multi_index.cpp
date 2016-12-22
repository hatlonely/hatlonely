//
//  multi_index.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/30.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  多重索引
//

#include <iostream>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost_multi_index {

// 类的属性作为索引
namespace {

struct employee {
    int id;
    std::string name;
    int age;
    
    employee(int id, const std::string &name, int age) : id(id), name(name), age(age) {}
    friend std::ostream& operator<<(std::ostream &os, const employee &e) {
        os << e.id << " " << e.name << " " << e.age;
        return os;
    }
};

// tag类，需要当做索引的属性
struct id {};
struct name {};
struct age {};

typedef boost::multi_index_container<
    employee,                                   // 容器元素
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<     // id索引，id唯一
            boost::multi_index::tag<id>, BOOST_MULTI_INDEX_MEMBER(employee, int, id)
        >,
        boost::multi_index::ordered_non_unique< // name索引，name不唯一
            boost::multi_index::tag<name>, BOOST_MULTI_INDEX_MEMBER(employee, std::string, name)
        >,
        boost::multi_index::ordered_non_unique< // age索引，age不唯一
            boost::multi_index::tag<age>, BOOST_MULTI_INDEX_MEMBER(employee, int, age)
        >
    >
> employee_set;     // 带索引的employee容器集合

void employee_main() {
    employee_set es;
    es.insert(employee(0, "Joe", 31));
    es.insert(employee(1, "Robert", 27));
    es.insert(employee(2, "John", 40));
    assert(!es.insert(employee(2, "Aristotle", 23)).second);  // 插入失败，因为id必须是唯一的
    es.insert(employee(3, "Albert", 20));
    assert(es.insert(employee(4, "John", 57)).second);          // 插入成功，name属性没有唯一要求
    
    {
        // 按id排序
        std::cout << "order by id: " << std::endl;
        // const typename boost::multi_index::index<employee_set, id>::type &index_id = boost::multi_index::get<id>(es);
        auto &index_id = boost::multi_index::get<id>(es);
        for (auto it = index_id.begin(); it != index_id.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << std::endl;
    } {
        // 按name排序
        std::cout << "order by name: " << std::endl;
        auto &index_name = boost::multi_index::get<name>(es);
        for (auto it = index_name.begin(); it != index_name.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << std::endl;
    } {
        // 按age排序
        std::cout << "order by age: " << std::endl;
        auto &index_age = boost::multi_index::get<age>(es);
        for (auto it = index_age.begin(); it != index_age.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << std::endl;
    }
    
    {
        // 精确查找
        auto its = boost::multi_index::get<id>(es).equal_range(1);
        for (auto it = its.first; it != its.second; ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << std::endl;
    } {
        // 范围查找
        auto it1 = boost::multi_index::get<age>(es).lower_bound(22);
        auto it2 = boost::multi_index::get<age>(es).upper_bound(35);
        for (auto it = it1; it != it2; ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << std::endl;
    }
}

}
    
// 类成员函数或者全局函数作为索引
namespace {

struct name_record
{
    std::string given_name;
    std::string family_name;
    
    name_record(std::string given_name, std::string family_name):
        given_name(given_name), family_name(family_name) {}
    
    std::string name() const {
        return family_name + " " + given_name;
    }
};
    
std::string::size_type name_record_length(const name_record &nr)
{
    return nr.name().size();
}
    
typedef boost::multi_index::multi_index_container<
    name_record,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<         // 按类成员函数name索引
            BOOST_MULTI_INDEX_CONST_MEM_FUN(name_record, std::string, name)
        >,
        boost::multi_index::ordered_non_unique<     // 按全局成员函数name_record_length索引
            boost::multi_index::global_fun<const name_record &, std::string::size_type, name_record_length>
        >
    >
> name_record_set;
    
void name_record_main() {
    name_record_set ns;
    ns.insert(name_record("Joe", "Smith"));
    ns.insert(name_record("Robert", "Nightingale"));
    ns.insert(name_record("Robert", "Brown"));
    ns.insert(name_record("Marc", "Tuxedo"));
    
    {
        // 按类成员函数name排序
        std::cout << "order by name: " << std::endl;
        for (auto it = ns.begin(); it != ns.end(); ++it) {
            std::cout << it->name() << " " << name_record_length(*it) << std::endl;
        }
        std::cout << std::endl;
    } {
        // 按全局函数name_record_length排序
        std::cout << "order by length: " << std::endl;
        for (auto it = boost::multi_index::get<1>(ns).begin(); it != boost::multi_index::get<1>(ns).end(); ++it) {
            std::cout << it->name() << " " << name_record_length(*it) << std::endl;
        }
        std::cout << std::endl;
    } {
        // 按name查找
        auto its = boost::multi_index::get<0>(ns).equal_range("Nightingale Robert");
        for (auto it = its.first; it != its.second; ++it) {
            std::cout << it->name() << " " << name_record_length(*it) << std::endl;
        }
        std::cout << std::endl;
    } {
        // 按length范围查找
        auto it1 = boost::multi_index::get<1>(ns).lower_bound(11);
        auto it2 = boost::multi_index::get<1>(ns).upper_bound(12);
        for (auto it = it1; it != it2; ++it) {
            std::cout << it->name() << " " << name_record_length(*it) << std::endl;
        }
    }
}

}

int main(int argc, const char *argv[]) {
    employee_main();
    name_record_main();
    
    return 0;
}

}