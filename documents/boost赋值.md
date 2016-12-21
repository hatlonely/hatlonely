# boost赋值

boost::assign库提供更方便更简单的对容器的赋值操作

## 容器初始化

```cpp
#include <boost/assign/list_of.hpp>
#include <list>
#include <map>
void assign_list_of_usage()
{
    using namespace boost::assign;

    std::list<int> primes = list_of(2)(3)(5)(7)(11);
    assert(primes.size() == 5);
    assert(primes.front() == 2);
    assert(primes.back() == 11);

    std::map<char, char> brackets = map_list_of('{', '}')('[', ']')('(', ')');
    assert(brackets.size() == 3);
    assert(brackets['{'] == '}');
    assert(brackets['['] == ']');
    assert(brackets['('] == ')');
}
```

## 容器插入

```cpp
#include <boost/assign/std/vector.hpp>
void assign_std_vector_usage()
{
    using namespace boost::assign;

    std::vector<int> values;
    values += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
    assert(values.size() == 10);
    assert(values[0] == 0);
    assert(values[9] == 9);
}

#include <boost/assign/list_inserter.hpp>
#include <map>
void assign_list_inserter_usage()
{
    using namespace boost::assign;

    std::map<std::string, int> months;
    insert(months)
        ("January",   31)("February", 28)("March",     31)("April",    30)
        ("May",       31)("June",     30)("July",      31)("August",   31)
        ("September", 30)("October",  31)("November",  30)("December", 31);
    assert(months.size() == 12);
    assert(months["January"] == 31);
    assert(months["December"] == 31);
}
```

## 总结

个人觉得这个库在写单测的时候可以用上，因为单测的时候可能经常要自己去构造一些数据，这个库能够很方便的帮我们构造一些数据，对可读性也有所提高，但是感觉在实际的代码中用途不是很大，因为只有很少的场景，我们需要对容器进行初始化赋值操作，插入的场景中容器自带的push_back，insert之类的函数已经能满足我们的需求，在c++11中，对容器的初始化赋值提供了语法上的支持，因此感觉这个库的意义也就不大了
