# boost字符串算法

字符串操作在现在的程序中几乎都会碰到，其重要性也就不用说了，而std::string中提供的字符串功能非常有限，boost的字符串算法正好弥补了这一不足

## 头文件

``` cpp
#include <boost/algorithm/string.hpp>
```

## 分类器

这些仿函数对字符进行分类，比如`is_any_of("1234567890")(c)`返回`c`是否为一个数字

``` cpp
// boost/algorithm/string/classification.hpp
void string_algorithm_classification_usage()
{
    // is_space, is_alnum, is_alpha, is_cntrl, is_digit,
    // is_graph, is_lower, is_upper, is_print, is_punct, is_xdigit,
    // is_any_of, is_from_range
    // 和ctype中提供的函数功能相同
    // 不同的是这些都是仿函数，可以作为谓词使用
}
```

## 谓词

谓词判断一个字符串是否符合某个条件
starts_with，ends_with，判断一个字符串是否以某个字符串开始或结束
contains，判断一个字符串是否包含另个字符串
lexicographical_compare，按字典顺序比较字符大小
all，判断一个字符串中所有字符是不是都是同一类
以i开头表示忽略大小写的比较

``` cpp
// boost/algorithm/string/predicate.hpp
void string_algorithm_predicate_usage()
{
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
```

## trim

trim函数一般用来去掉前后空白字符，也可以用分类器去掉任一类字符

``` cpp
// boost/algorithm/string/trim.hpp
void string_algorithm_trim_usage()
{
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
```

## 查找替换

std::string中也有replace函数，但是其功能和这里的不同，boost的replace功能更加强大，基本可以满足我们所有的查找替换需求，更加复杂的可能就需要用到正则匹配替换了

``` cpp
// boost/algorithm/string/find.hpp
void string_algorithm_find_usage()
{
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
}
```

## 字符串分割

c库里面有个token函数来分割字符串，用起来比较麻烦，这个split函数与其他语言的实现类似，直接将分割的结果放到一个容器中

``` cpp
// boost/algorithm/string/split.hpp
void string_algorithm_split_usage()
{
    std::vector<std::string> result;
    boost::split(result, "hatlonely\tplayjokes\trobin\tsissie\tsky", boost::is_any_of("\t"));
    assert(result.size() == 5);
    assert(result[0] == "hatlonely");
    assert(result[1] == "playjokes");
    assert(result[2] == "robin");
    assert(result[3] == "sissie");
    assert(result[4] == "sky");
}
```

## 字符串合并

合并其实就是分割的逆操作，将字符串数组组合成一个字符串

``` cpp
// boost/algorithm/string/join.hpp
void string_algorithm_join_usage()
{
    std::vector<std::string> result;
    result.push_back("hatlonely");
    result.push_back("playjokes");
    result.push_back("robin");
    result.push_back("sissie");
    result.push_back("sky");
    assert(boost::join(result, ", ") == "hatlonely, playjokes, robin, sissie, sky");
}
```
