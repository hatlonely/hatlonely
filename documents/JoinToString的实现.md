# JoinToString的实现

## 问题场景

在工作中经常会有类似打印一个数组的需求，而c++又不像python之类的语言可以直接输出数组，每次都需要写一个循环，而在日志输出的场景中，希望能把数组先拼成一个字符串再输出，当然可以每次都写一个类似这样的循环

``` c++
std::stringstream os;
for (auto &element : container) {
    os << element << ", ";
}
log("%s", os.str().c_str());
```

但是这样的循环一多，就显得很复杂和冗余

万能的boost提供了 `boost::join` 函数，但是只能 join 字符串数组，并不能解决 join 任意类型数组

## 问题描述

实现一个函数，将任意容器中的元素转成字符串，例如将数组 {1, 2, 3, 4} 转成字符串 1, 2, 3, 4

## 实现

用模板实现任意类型的 join

``` c++
namespace join_to_string_v1 {

template <typename T>
std::string JoinToString(const T& container) {
    std::stringstream os;
    for (const auto& element : container) {
        os << element << ", ";
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - 2, 2);
    }
    return result;
}

int main(int argc, const char* argv[]) {
    std::vector<int> vi = {1, 2, 3, 4};
    std::cout << "[" << JoinToString(vi) << "]" << std::endl;   // [1, 2, 3, 4]

    return 0;
}

} // join_to_string_v1
```

有时候我们只需要打印容器中的某个区间，并不需要打印所有的元素，使用迭代器作为参数，可以带来更多的灵活性

``` c++
namespace join_to_string_v2 {

// 使用迭代器作为模板打印一个数组区间，增加灵活性
template <typename Iterator>
std::string JoinToString(Iterator begin, Iterator end) {
    std::stringstream os;
    for (auto it = begin; it != end; ++it) {
        os << *it << ", ";
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - 2, 2);
    }
    return result;
}

int main(int argc, const char* argv[]) {
    std::vector<int> vi = {1, 2, 3, 4};
    std::cout << "[" << JoinToString(vi.begin(), vi.end()) << "]" << std::endl;     // [1, 2, 3, 4]
    std::cout << "[" << JoinToString(vi.begin() + 1, vi.end()) << "]" << std::endl; // [2, 3, 4]

    return 0;
}

} // join_to_string_v2
```

有时候我们的容器中装的是自定义类型，一种方式是实现在v2的版本中为每一个自定义类型实现 `operator <<` 操作，但大多数情况下，我们只需要打印这个类型中的某个字段，可以考虑再提供一个function的参数，支持传入函数操作元素

``` c++
namespace join_to_string_v3 {

#ifndef MAKE_JOIN_STRING_HELPER
#define MAKE_JOIN_STRING_HELPER(Class, Type, field) \
    struct JoinToStringHelper_##Class##_##field { \
        const Type& operator()(const Class& t) { \
        return t.field; \
    } \
};
#endif

template <typename T>
struct JoinToStringHelper {
    const T& operator()(const T& t) {
        return t;
    }
};

// 增加函数模板参数，支持打印类的某些字段
template <typename Iterator, typename Function=JoinToStringHelper<typename Iterator::value_type>>
std::string JoinToString(Iterator begin, Iterator end, Function function=Function()) {
    std::stringstream os;
    for (auto it = begin; it != end; ++it) {
        os << function(*it) << ", ";
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - 2, 2);
    }
    return result;
}

int main(int argc, const char* argv[]) {
    {
        std::vector<int> vi = {1, 2, 3, 4};
        std::cout << "[" << JoinToString(vi.begin(), vi.end()) << "]" << std::endl; // [1, 2, 3, 4]
    } {
        struct A {
            int i;
            int j;
        };

        MAKE_JOIN_STRING_HELPER(A, int, i);
        MAKE_JOIN_STRING_HELPER(A, int, j);

        std::vector<A> va = {{1, 11}, {2, 22}, {3, 33}};
        std::cout << "[" << JoinToString(va.begin(), va.end(), JoinToStringHelper_A_i()) << "]"
                << std::endl;       // [1, 2, 3]
        std::cout << "[" << JoinToString(va.begin(), va.end(), JoinToStringHelper_A_j()) << "]"
                << std::endl;       // [11, 22, 33]
    }

    return 0;
}

} // join_to_string_v3
```

我们希望分隔符号可以自己设置，用逗号分隔便于阅读，用`tab`分隔便于统计分析

``` cpp
namespace join_to_string_v4 {

#ifndef MAKE_JOIN_STRING_HELPER
#define MAKE_JOIN_STRING_HELPER(Class, Type, field) \
    struct JoinToStringHelper_##Class##_##field { \
        const Type& operator()(const Class& t) { \
        return t.field; \
    } \
};
#endif

template <typename T>
struct JoinToStringHelper {
    const T& operator()(const T& t) {
        return t;
    }
};

// 增加separator参数，支持分隔符设置
template <typename Iterator, typename Function=JoinToStringHelper<typename Iterator::value_type>>
std::string JoinToString(Iterator begin, Iterator end,
                         std::string separator=", ", Function function=Function()) {
    std::stringstream os;
    for (auto it = begin; it != end; ++it) {
        os << function(*it) << separator;
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - separator.length(), separator.length());
    }
    return result;
}

int main(int argc, const char* argv[]) {
    {
        std::vector<int> vi = {1, 2, 3, 4};
        std::cout << "[" << JoinToString(vi.begin(), vi.end()) << "]" << std::endl;      // [1, 2, 3, 4]
        std::cout << "[" << JoinToString(vi.begin(), vi.end(), "|") << "]" << std::endl; // [[1|2|3|4]
    } {
        struct A {
            int i;
            int j;
        };

        MAKE_JOIN_STRING_HELPER(A, int, i);
        MAKE_JOIN_STRING_HELPER(A, int, j);

        std::vector<A> va = {{1, 11}, {2, 22}, {3, 33}};
        std::cout << "[" << JoinToString(va.begin(), va.end(), ", ", JoinToStringHelper_A_i()) << "]"
            << std::endl;       // [1, 2, 3]
        std::cout << "[" << JoinToString(va.begin(), va.end(), ", ", JoinToStringHelper_A_j()) << "]"
            << std::endl;       // [11, 22, 33]
    }

    return 0;
}

} // join_to_string_v4
```

## 链接

- [github源码](https://github.com/hatlonely/crystal/blob/master/codesnips/join_to_string.hpp)
