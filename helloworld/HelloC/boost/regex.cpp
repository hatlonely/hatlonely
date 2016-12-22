//
//  regex.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//

#include <iostream>
#include <map>
#include <boost/regex.hpp>

namespace boost_regex {

// regex_match，完全匹配
void regex_match_usage() {
    // boost::regex email_regex("\\w+@\\w+\\.com", boost::regex::icase);
    boost::regex email_regex("\\w+@\\w+\\.com");
    std::string email = "hatlonely@gmail.com";
    assert(boost::regex_match(email, email_regex));
}

// regex_search，从目标串中找到匹配串
// 只匹配一个
void regex_search_usage() {
    // 从log中提取[ key: value ]
    boost::regex log_regex(
                           "\\[\\s*"       // [
                           "(\\w+)"        // key值
                           "\\s*:\\s*"     // 冒号，前后允许空白
                           "(\\w+)"        // value值
                           "\\s*\\]");     // ]
    std::string log = "NOTICE: [ proc_time: 12345 ] [ request_type: 4 ]";
    boost::smatch result;
    assert(boost::regex_search(log, result, log_regex));
    assert(result.size() == 3);
    // result[0] 为匹配到的串
    // result[n] 为匹配到的第n个字串
    assert(result[0] == "[ proc_time: 12345 ]");
    assert(result[1] == "proc_time");
    assert(result[2] == "12345");
    // result.prefix() 未匹配到的之前的串
    // result.suffix() 未匹配到的之后的串
    assert(result.prefix() == "NOTICE: ");
    assert(result.suffix() == " [ request_type: 4 ]");
}

// regex_replace，正则替换
void regex_replace_usage() {
    // proc_time 后面加上单位 us
    // $` 未匹配到的之前的串
    // $& 匹配到的串
    // $' 未匹配到的之后的串
    // $n n为0-9的数字，表示匹配到的第n个字串（括号包围）
    std::string str = boost::regex_replace(
                                           std::string("NOTICE: [ proc_time: 12345 ]"),
                                           boost::regex("proc_time"),
                                           "$&_us");
    assert(str == "NOTICE: [ proc_time_us: 12345 ]");
    
    // 把"cout << a & b << endl"转成HTML格式
    std::string orig_str = "cout << a & b << endl";
    std::string special_char = "(<)|(>)|(&)|(\")";
    // ?n 表示把第几个字串替换成新字串
    std::string escape_char = "(?1&lt;)(?2&gt;)(?3&amp;)(?4&quot)";
    std::string html_str = boost::regex_replace(
                                                orig_str,
                                                boost::regex(special_char),
                                                escape_char,
                                                boost::match_default | boost::format_all);
    assert(html_str == "cout &lt;&lt; a &amp; b &lt;&lt; endl");
}

// 通过迭代器匹配所有目标串
// 迭代器的value_type为match_result
void regex_iterator_usage() {
    // 从log中提取[ key: value ]
    boost::regex log_regex(
                           "\\[\\s*"       // [
                           "(\\w+)"        // key值
                           "\\s*:\\s*"     // 冒号，前后允许空白
                           "(\\w+)"        // value值
                           "\\s*\\]");     // ]
    std::string log = "NOTICE: [ proc_time: 12345 ] [ request_type: 4 ]";
    boost::sregex_iterator begin(log.begin(), log.end(), log_regex);
    boost::sregex_iterator end;
    
    boost::sregex_iterator it = begin;
    assert(it->size() == 3);
    assert((*it)[0] == "[ proc_time: 12345 ]");
    assert((*it)[1] == "proc_time");
    assert((*it)[2] == "12345");
    ++it;
    assert(it->size() == 3);
    assert((*it)[0] == "[ request_type: 4 ]");
    assert((*it)[1] == "request_type");
    assert((*it)[2] == "4");
    
    std::map<std::string, std::string> key_value;
    for (boost::sregex_iterator it = begin; it != end; ++it) {
        key_value[(*it)[1]] = ((*it)[2]);
    }
    assert(key_value.size() == 2);
    assert(key_value["proc_time"] == "12345");
    assert(key_value["request_type"] == "4");
}

// 和regex_iterator类似，迭代器的value_type为sub_match
void regex_token_iterator_usage() {
    // 从log中提取[ key: value ]
    boost::regex log_regex(
                           "\\[\\s*"       // [
                           "(\\w+)"        // key值
                           "\\s*:\\s*"     // 冒号，前后允许空白
                           "(\\w+)"        // value值
                           "\\s*\\]");     // ]
    std::string log = "NOTICE: [ proc_time: 12345 ] [ request_type: 4 ]";
    boost::sregex_token_iterator begin(log.begin(), log.end(), log_regex);
    boost::sregex_token_iterator end;
    
    std::vector<std::string> matchs;
    for (boost::sregex_token_iterator it = begin; it != end; ++it) {
        matchs.push_back(*it);
    }
    assert(matchs.size() == 2);
    assert(matchs[0] == "[ proc_time: 12345 ]");
    assert(matchs[1] == "[ request_type: 4 ]");
}

int main(int argc, const char *argv[]) {
    regex_match_usage();
    regex_search_usage();
    regex_replace_usage();
    regex_iterator_usage();
    regex_token_iterator_usage();
    return 0;
}

}