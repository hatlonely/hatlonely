//
//  math.cpp
//  HelloC
//
//  Created by hatlonely on 16/1/10.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <boost/math/common_factor.hpp>
#include <boost/multiprecision/gmp.hpp>

namespace boost_math {
    
int main(int argc, const char *argv[]) {
    {
        // 最大公约数和最小公倍数
        assert(boost::math::gcd(36, 24) == 12);
        assert(boost::math::lcm(36, 24) == 72);
    } {
        // 无限精度整数
        {
            // 依赖gmp库，
            // mac gmp库安装: sudo brew install gmp
            boost::multiprecision::mpz_int v = 1;
            for (uint32_t i = 1; i <= 1000; i++) {
                v *= i;
            }
            std::cout << v << std::endl;
        }
    }
    
    return 0;
}

}