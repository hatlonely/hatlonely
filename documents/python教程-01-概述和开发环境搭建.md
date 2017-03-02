# 概述和开发环境搭建

## 概述

### 一首打油诗

**优雅**、**明确**、**简单**

官网链接：<https://www.python.org/>

```
Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.Complex is better than complicated.
Flat is better than nested.Sparse is better than dense.
Readability counts.Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than *right* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those!
```

### Python的应用场景

**Web应用**

快速搭建Restful服务，快速写一个某种服务的demo，调研服务的可行性；或者搭建对性能要求并不高的服务

**爬虫**

Python很适合网络爬虫的开发，PyQuery可以像jQuery一样处理dom，非常方便，http相关的库也很完善，但是同时也有局限，动态页面的抓取不是很方便（当然这个问题本身就比较复杂）

**各种client脚本**

Thrift，grpc基本这些网络框架都会支持python，python的client有一个优势，不用编译，可以随时修改，而且可以轻松的跨平台

**文本处理**

python很擅长文本处理，正则表达式库和基本的字符串处理库都很友好、方便

**数据统计分析**

Python的numpy库提供很完备的数据分析功能，python简洁的语法能让我们很友好地去使用这些功能，并且还能很方便地生成需要的格式

**临时脚本**

我们会用python来作一些临时的较为复杂的数据统计（简单的shell无法胜任，或者很难支持的那种），同时这些功能又比较松散临时

## 开发环境搭建

### 快速安装

**Mac**

```
brew install python3
```

**Centos**

```
yum install python3
```

### 源码安装

```
wget https://www.python.org/ftp/python/3.6.0/Python-3.6.0.tgz
tar -xzf Python-3.6.0.tgz
cd Python-3.6.0
./configure --prefix=`pwd`/output
make -j8 && make install
```

### IDE-PyCharm

下载链接：<https://www.jetbrains.com/pycharm/>

![pycharm-img](https://www.jetbrains.com/pycharm/img/screenshots/complexLook@2x.jpg)

## Hello World

``` python
#!/usr/bin/env python3

def main():
    print('hello world')

if __name__ == '__main__':
    main()

```



