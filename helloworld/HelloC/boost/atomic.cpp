//
//  atomic.cpp
//  HelloC
//
//  Created by hatlonely on 16/2/16.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <boost/atomic.hpp>

namespace boost_atomic {
    
int main(int argc, const char *argv[]) {
    {
        boost::atomic<int> i(10);
        i++;
        i += 10;
        i = 22;
        std::cout << i << std::endl;
        i.load();
        i.store(100);
        std::cout << i << std::endl;
    }

    return 0;
}

}
