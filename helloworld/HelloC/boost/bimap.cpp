//
//  bimap.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/29.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  双端map，相当于std::map<key, value>和std::map<value, key>的组合
//

#include <iostream>
#include <string>
#include <boost/bimap.hpp>

namespace boost_bimap {

int main(int argc, const char *argv[]) {
    boost::bimap<int, std::string> bm;
    bm.insert(boost::bimap<int, std::string>::value_type(1, "sissie"));
    bm.insert(boost::bimap<int, std::string>::value_type(2, "playjokes"));
    bm.insert(boost::bimap<int, std::string>::value_type(3, "robin"));
    bm.insert(boost::bimap<int, std::string>::value_type(4, "sky"));
    bm.insert(boost::bimap<int, std::string>::value_type(5, "hatlonely"));
    
    std::cout << "bm.left.at(1) -> " << bm.left.at(1) << std::endl;
    std::cout << "bm.right.at(\"sissie\") -> " << bm.right.at("sissie") << std::endl;
    
    for (auto it = bm.left.begin(); it != bm.left.end(); ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }

    return 0;
}

}
