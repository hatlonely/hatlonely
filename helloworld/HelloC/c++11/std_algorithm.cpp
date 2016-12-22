//
//  std_algorithm.cpp
//  HELLOC
//
//  Created by hatlonely on 16/9/26.
//
//

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

namespace c11_std_algorithm {
    
int main(int argc, const char *argv[]) {
    {
        std::set<int> iset1 = {4, 5, 6, 7};
        std::set<int> iset2 = {8, 9, 6, 7};
        std::vector<int> result;
        // result = iset1 - iset2  =>  {4, 5}
        std::set_difference(iset1.begin(), iset1.end(), iset2.begin(), iset2.end(),
                            std::inserter(result, result.begin()));
        std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    } {
        std::set<int> iset1 = {4, 5, 6, 7};
        std::set<int> iset2 = {9, 8, 6, 7};
        std::vector<int> result;
        // result = iset2 - iset1  =>  {8, 9}
        std::set_difference(iset2.begin(), iset2.end(), iset1.begin(), iset1.end(),
                            std::inserter(result, result.begin()));
        std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }

    return 0;
}
    
}
