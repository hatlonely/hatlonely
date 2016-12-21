# javascrpit权威指南

Davivd Flanagan 著 淘宝前端团队 译

## 词法结构

- 区分大小写
- 注释，// 和 /*  */
- 分号可选，但建议每句话后面都加一个分号

## 类型、值和变量

- 不区分整数和浮点数，数值常量，6.02e23、1.4738223E-32
- 数学运算Math类
- 浮点数不精确，.3 - .2 != .2 -.1
- 日期，Date类
- 字符串可以用'或"
- 正则表达式/RegExp/
- 布尔值，true和false
- null表示对象有定义但是值为空和undefined表示该对象还未定义
- null == undefined, null !== undefined, '0' == 0, '0' !== 0
- 显式类型转换

    ```javascript
    '' + x // 转成String
    + x    // 转成Number
    !!x    // 转成Boolean
    ```

- 变量作用域，var声明局部变量，否则全局变量，作用域以函数为单位

## 表达式和运算符

- [] 空数组，{} 空对象
- 函数，function add(x, y) {return a + b;}
- 属性访问有两种方式：expression.identifier 和 expression[expression]
- 对象创建表达式 var o = new Object()
- 运算符：

        delete  删除属性
        typeof  检测操作数类型
        void    返回undefined
        in      测试属性是否存在
        instanceof  测试对象类
        >>      有符号右移
        >>>     无符号右移

- eval()，把字符串当做javascript代码解析

## 语句

- var 声明变量
- function 定义函数
- if, else, switch, do/while, while, for, for/in, break, continue,
- return, throw, try/catch/finally,
- with, debugger, use strict

## 对象

- 创建对象，new Object() 或 Object.create()
- prototype

## 数组

- 数组长度，[].length
- push(), pop(), shift(), unshift()
- join(), reverse(), sort(), concat(), slice(), splice()
- toString(), toLocalString()
- forEach(), map(), filter(), every(), some(), reduce(), reduceRight()
- indexOf(), lastIndexOf()

## 函数

``` javascript
function add(x, y) { return x + y; }
var add = function (x, y) { return x + y; }
var add = new Function('x', 'y', 'return x + y;')

// 模块：
(function () {
    // 模块代码
}());

fun.call(obj, ...), fun.apply(obj, [...])
var objFun = fun.bind(obj, ...)
```

## 类和模块

```
F.prototype.constructor == F
```

## 正则表达式

``` javascript
var pattern = /s$/, var pattern = new RegExp('s$')
\uxxxx 指定十六进制Unicode字符
```

- 字符类

        [...]   匹配括号内任意字符
        [^...]  匹配不在括号内任意字符
        .       除换行符和其他Unicode行终止符之外任意字符
        \w      和[a-zA-Z0-9]等价
        \W      和[^a-zA-Z0-9]等价
        \s      匹配任何Unicode空白
        \S      匹配任何非Unicode空白
        \d      和[0-9]等价
        \D      和[^0-9]等价

- 重复

        {n, m}  匹配前一项至少n次，但不超过m次
        {n, }   匹配前一项n次或者更多次
        {n}     匹配前一项n次
        ?       0次或1次，等价于{0, 1}
        +       1次或多次，等价于{1, }
        *       0次或多次，等价于{0, }
        ??, +?, *?   非贪婪

- 选择，分组和引用

        |        选择
        (...)    分组并记忆（用于引用）
        (?:...)  分组但不记忆
        \n       引用第n个分组

- 位置匹配

        ^      匹配字符串开头，多行检索中，匹配行首
        $      匹配字符串结尾，多行检索中，匹配行尾
        \b     匹配单词边界，即\w和\W之间的位置
        \B     非单词边界
        (?=p)  接下来的字符与p匹配的位置
        (?!p)  接下来的字符与p不匹配的位置

- 修饰符

        i  不区分大小写
        g  执行一个全局匹配，匹配所有，而不是找到一个后停止
        m  多行匹配

- 例子

        'JavaScript'.search(/script/i);  // 返回4
        // 替换text中所有不区分大小写的javascript成JavaScript
        text.replace(/javascript/gi, 'JavaScript');
