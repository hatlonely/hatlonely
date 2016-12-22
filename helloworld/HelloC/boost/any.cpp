//
//  any.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//

#include <iostream>
#include <list>
#include <boost/any.hpp>

namespace boost_any {

int main(int argc, const char *argv[]) {
    std::list<boost::any> any_list;
    any_list.push_back(10);
    any_list.push_back(std::string("hatlonely"));
    
    try {
        for (std::list<boost::any>::iterator iter = any_list.begin();
             iter != any_list.end(); ++iter) {
            if (iter->type() == typeid(int)) {
                std::cout << boost::any_cast<int>(*iter) << std::endl;
            } else if (iter->type() == typeid(std::string)) {
                std::cout << boost::any_cast<std::string>(*iter).c_str() << std::endl;
            }
        }
    } catch (boost::bad_any_cast &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

}