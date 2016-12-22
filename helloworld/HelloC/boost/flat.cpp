//
//  flat.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/29.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  flat_(multi)map/set
//  排序的数组容器，插入性能差，查询性能和map/set一样，比map/set节省内存
//

#include <iostream>
#include <string>
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>

namespace boost_flat {

int main(int argc, const char *argv[]) {
    {
        boost::container::flat_map<std::string, int> fm;
        fm["one"] = 1;
        fm["two"] = 2;
        for (auto it = fm.begin(); it != fm.end(); ++it) {
            std::cout << it->first << " => " << it->second << std::endl;
        }
        std::cout << std::endl;
    } {
        boost::container::flat_multimap<std::string, int> fmm;
        fmm.insert(boost::container::flat_multimap<std::string, int>::value_type("one", 1));
        fmm.insert(boost::container::flat_multimap<std::string, int>::value_type("two", 2));
        fmm.insert(boost::container::flat_multimap<std::string, int>::value_type("one", 11));
        for (auto it = fmm.begin(); it != fmm.end(); ++it) {
            std::cout << it->first << " => " << it->second << std::endl;
        }
        std::cout << std::endl;
    } {
        boost::container::flat_set<std::string> fs;
        fs.insert("robin");
        fs.insert("sky");
        fs.insert("sissie");
        fs.insert("hatlonely");
        fs.insert("playjokes");
        fs.insert("sissie");
        for (auto it = fs.begin(); it != fs.end(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    } {
        boost::container::flat_multiset<std::string> fms;
        fms.insert("robin");
        fms.insert("sky");
        fms.insert("sissie");
        fms.insert("hatlonely");
        fms.insert("playjokes");
        fms.insert("sissie");
        for (auto it = fms.begin(); it != fms.end(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
    
}