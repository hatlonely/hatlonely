//
//  regex.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//


#include <iostream>
#include <regex>
#include <cassert>

namespace c11_regex {

int main(int argc, const char *argv[]) {
    std::string context = ""
    "hatlonely (hatlonely@gmail.com) "
    "playjokes (playjokes@gmail.com)";
    
    std::regex mail_regex("(\\w+)@(\\w+)\\.com");
    std::smatch mail_result;
    
    // 不能全词匹配 regex_match返回false
    assert(!std::regex_match(context, mail_result, mail_regex));
    // 可以部分匹配 regex_search返回true
    assert(std::regex_search(context, mail_result, mail_regex));
    // mail_result被regex_search设置过 返回true
    assert(mail_result.ready());
    // mail_result中sub_match的个数，两个子表达式加上整个表达式
    assert(mail_result.size() == 3);
    // mail_result[0]为匹配到的整个字符串
    assert(mail_result[0] == "hatlonely@gmail.com");
    // mail_result[n]为第n个子表达式匹配到得串（小括号内的串）
    assert(mail_result[1] == "hatlonely");
    assert(mail_result[2] == "gmail");
    // prefix未匹配到的之前的串
    assert(mail_result.prefix() == "hatlonely (");
    // suffix未匹配到的之后的串
    assert(mail_result.suffix() == ") playjokes (playjokes@gmail.com)");
    // $`  相当于prefix
    // $'  相当于suffix
    // $n  第n个子匹配
    std::cout << mail_result.format("$` $1 $2") << std::endl;
    
    {
        // 相当于循环调用regex_search，迭代器的value_type为match_result
        std::sregex_iterator it(context.begin(), context.end(), mail_regex);
        std::sregex_iterator end;
        for (; it != end; ++it) {
            std::cout << (*it)[0] << std::endl;
        }
    }
    {
        // 相当于循环调用regex_search，迭代器的value_type为sub_match，相当于match_result[0]
        std::sregex_token_iterator it(context.begin(), context.end(), mail_regex);
        std::sregex_token_iterator end;
        for (; it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }
    
    {
        // regex_replace 默认会替换所有匹配到的串，指定format_first_only可以只替换第一个匹配到得串
        // hatlonely (hatlonely@gmail.com) playjokes (playjokes@gmail.com)
        std::cout << context << std::endl;
        // hatlonely (hatlonely) playjokes (playjokes)
        std::cout << regex_replace(context, mail_regex, "$1") << std::endl;
        // hatlonely (hatlonely) playjokes (playjokes@gmail.com)
        std::cout << regex_replace(context, mail_regex, "$1",
                                   std::regex_constants::format_first_only) << std::endl;
    }
    
    return 0;
}

}
