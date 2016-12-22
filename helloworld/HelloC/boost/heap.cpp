//
//  heap.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/29.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  最大堆，这个东西std里面也有
//


#include <iostream>
#include <boost/heap/priority_queue.hpp>

namespace boost_heap {

int main(int argc, const char *argv[]) {
    boost::heap::priority_queue<int> pq;
    
    pq.push(4);
    pq.push(1);
    pq.push(3);
    pq.push(2);
    
    for (boost::heap::priority_queue<int>::iterator it = pq.begin(); it != pq.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
    
    assert(pq.top() == 4);
    pq.pop();
    assert(pq.top() == 3);
    pq.pop();
    assert(pq.top() == 2);
    pq.pop();
    assert(pq.top() == 1);
    
    return 0;
}

}