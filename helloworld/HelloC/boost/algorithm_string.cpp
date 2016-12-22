//
//  algorithm_string.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  一些和字符串相关的算法
//

#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

namespace boost_algorithm_string {

// boost/algorithm/string/classification.hpp
void string_algorithm_classification_usage() {
    // is_space, is_alnum, is_alpha, is_cntrl, is_digit,
    // is_graph, is_lower, is_upper, is_print, is_punct, is_xdigit,
    // is_any_of, is_from_range
    // 和ctype中提供的函数功能相同
    // 不同的是这些都是仿函数，可以作为谓词使用
}

// boost/algorithm/string/predicate.hpp
void string_algorithm_predicate_usage() {
    // starts_with, istarts_with, ends_with, iends_with
    assert(boost::starts_with("Get busy living or get busy dieing", "Get"));
    assert(!boost::starts_with("Get busy living or get busy dieing", "get"));
    assert(boost::istarts_with("Get busy living or get busy dieing", "get"));
    // contains, icontains
    assert(boost::contains("Get busy living or get busy dieing", "living"));
    // equals, iequals
    assert(boost::iequals("Get busy living", "GET BUSY LIVING"));
    // lexicographical_compare
    assert(boost::lexicographical_compare("aabbc", "aabbd"));
    // all
    assert(boost::all("get busy dieing", boost::is_from_range('a', 'z') || boost::is_space()));
}

// boost/algorithm/string/trim.hpp
void string_algorithm_trim_usage() {
    // trim
    std::string string_to_trim;
    string_to_trim = " \t  Hello World   \n";
    boost::trim(string_to_trim);
    assert("Hello World" == string_to_trim);
    
    // trim_left, trim_right
    string_to_trim = " \t  Hello World   \n";
    boost::trim_left(string_to_trim);
    assert("Hello World   \n" == string_to_trim);
    
    // trim_copy, trim_left_copy, trim_right_copy
    string_to_trim = " \t  Hello World   \n";
    assert("Hello World" == boost::trim_copy(string_to_trim));
    assert(" \t  Hello World   \n" == string_to_trim);
    
    // trim_if, trim_left_if, trim_right_if
    // trim_copy_if, trim_left_copy_if, trim_right_copy_if
    string_to_trim = "  Hello World\n  ";
    assert("Hello World\n" == boost::trim_copy_if(string_to_trim, boost::is_any_of(" ")));
}

// boost/algorithm/string/find.hpp
void string_algorithm_find_usage() {
    // find, find_first, ifind_first, find_last, ifind_last,
    // find_nth, ifind_nth, find_head, find_tail, find_token
    //
    // replace_range_copy, replace_range, replace_first_copy, replace_first,
    // ireplace_first_copy, ireplace_first, replace_last_copy, replace_last,
    // ireplace_last_copy, ireplace_last, replace_nth_copy, replace_nth,
    // ireplace_nth_copy, ireplace_nth, replace_all_copy, replace_all,
    // ireplace_all_copy, ireplace_all, replace_head_copy, replace_head,
    // replace_tail_copy, replace_tail
    std::string result = "playjokes, sky, sissie";
    boost::replace_all(result, ", ", " ");
    assert(result == "playjokes sky sissie");
    std::string a = "sissie";
    std::string b = "ss";
    boost::ifind_first(a, b);
}

// boost/algorithm/string/split.hpp
void string_algorithm_split_usage() {
    std::vector<std::string> result;
    boost::split(result, "hatlonely\tplayjokes\trobin\tsissie\tsky", boost::is_any_of("\t"));
    assert(result.size() == 5);
    assert(result[0] == "hatlonely");
    assert(result[1] == "playjokes");
    assert(result[2] == "robin");
    assert(result[3] == "sissie");
    assert(result[4] == "sky");
}

// boost/algorithm/string/join.hpp
void string_algorithm_join_usage() {
    std::vector<std::string> result;
    result.push_back("hatlonely");
    result.push_back("playjokes");
    result.push_back("robin");
    result.push_back("sissie");
    result.push_back("sky");
    assert(boost::join(result, ", ") == "hatlonely, playjokes, robin, sissie, sky");
}

int main(int argc, const char *argv[]) {
    string_algorithm_predicate_usage();
    string_algorithm_trim_usage();
    string_algorithm_find_usage();
    string_algorithm_split_usage();
    string_algorithm_join_usage();
    string_algorithm_classification_usage();
    return 0;
}

}