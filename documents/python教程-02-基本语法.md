# 基本语法

## 基本数据结构

python是一种动态语言，变量有类型，但是变量不和类型绑定
字面语法非常友好

```python
anumber = 10
avery_big_number = 10000000000000000000000
astring = 'hatlonely'
atuple = ('hatlonely', 'hatlonely@foxmail.com', 25, '1234567890')
alist = ['hatlonely', 'hatlonely@foxmail.com', 25, '1234567890']
aset = {'hatlonely', 'hatlonely@foxmail.com', 25, '1234567890'}
adict = {
    'name': 'hatlonely',
    'mail': 'hatlonely@foxmail.com',
    'telphone': '1234567890',
    'age': 25
}
```

## 控制流

python简洁的哲学，使用缩进来表示代码块，行尾不加分号，条件不加括号，减少敲击键盘的次数

```python
number = 1

# if 条件
if number > 0:
    print('positive')
elif number < 0:
    print('negtive')
else:
    print('zero')

# for 循环
for i in range(0, 10):
    print(i)

alist = ['hatlonely', 'hatlonely@foxmail.com', 25, '1234567890']
for element in alist:
    print(element)

for line in open('1_hello_world.py', encoding='utf-8'):
    print(line.strip())

adict = {
    'name': 'hatlonely',
    'mail': 'hatlonely@foxmail.com',
    'telphone': '1234567890',
    'age': 25
}
for key in adict:
    print('{} = {}'.format(key, adict[key]))
for key in sorted(adict.keys()):
    print('{} = {}'.format(key, adict[key]))

# while 循环
while True:
    print('hello world')
    break
```

## 函数

支持以元组的形式返回多个值

```python
def add(a, b):
    return a + b

def make_person():
    return ('hatlonely', 25)

name, age = make_erson()
print('name: {}, age: {}'.format(name, age))
```

## lambda

lambda可以理解为匿名函数，语法:
    `lambda <参数列表>: <返回结果>`
例如:
    `lambda x, y: x + y`
参数有两个 `x` 和 `y` 返回 `x + y`

```python
add = lambda x, y: x + y
# 相当于
# def add(x, y):
#     return x + y
print(add(4,5))

alist = [1, 2, 3, 4, 5]
alist = list(map(lambda x: x+1, alist))
print(alist)
```

## 类

成员变量用 `self.xxx` 定义
成员函数第一个参数都是 `self`，相当于 `this` 指针，指代对象本身，获取成员变量以及调用其他成员函数都需要通过这个参数
`class Derive(Base)` 表示 `Derive` 从 `Base` 继承而来，继承的方法需要显式通过 `Base` 调用

```python
class Base(object):
    def __init__(self):
        self.name = 'hatlonely'
        print('construct base')

    def say_hello(self):
        print('hello {}'.format(self.name))

base = Base()
base.say_hello()

class Derive(Base):
    def __init__(self):
        Base.__init__(self)
        print('construct derive')

derive = Derive()
derive.say_hello()
```

## 异常

使用 `raise` 抛出异常，使用 `try...except` 捕获异常

```python
def div(x, y):
    if y == 0:
        raise ZeroDivisionError('ZeroDivisionError: x={0}, y={1}'.format(x, y))
    return x / y

try:
    div(2, 0)
except ZeroDivisionError as error:
    print(error)
```

## 作业

1.创建一个员工类（Employee），你的员工都应该有姓名，职级
2.公司的职称和薪水有如下的对应关系： 经理：50000，主管：20000，员工：10000
3.让你的Employee会自我介绍，自我介绍的内容包括姓名，职级以及薪水
4.你有一个经理，两个主管，五个员工
5.召开一次会议，所有的员工都自我介绍一遍


