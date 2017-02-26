# 基本语法

## 基本数据结构

```python
anumber = 10
averyBigNumber = 10000000000000000000000
astring = 'hatlonely'
atuple = ('hatlonely', 'hatlonely@foxmail.com', 25, '13810245740')
alist = ['hatlonely', 'hatlonely@foxmail.com', 25, '13810245740']
adict = {
    'name': 'hatlonely',
    'mail': 'hatlonely@foxmail.com',
    'telphone': '13810245740',
    'age': 25
}
```

## 控制流

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

alist = ['hatlonely', 'hatlonely@foxmail.com', 25, '13810245740']
for element in alist:
    print(element)

for line in open('1_hello_world.py', encoding='utf-8'):
    print(line.strip())

adict = {
    'name': 'hatlonely',
    'mail': 'hatlonely@foxmail.com',
    'telphone': '13810245740',
    'age': 25
}
for key in adict:
    print('{0} = {1}'.format(key, adict[key]))
for key in sorted(adict.keys()):
    print('{0} = {1}'.format(key, adict[key]))

# while 循环
while True:
    print('hello world')
    break
```

## 函数

```python
def add(a, b):
    return a + b

def makePerson():
    return ('hatlonely', 25)

name, age = makePerson
print('name: {0}, age: {1}'.format(name, age))
```

## lambda

```python
add = lambda x,y: x + y
print(add(4,5))

alist = [1, 2, 3, 4, 5]
alist = list(map(lambda x: x+1, alist))
print(alist)
```

## 类

```python
class Base(object):
    def __init__(self):
        self.name = 'hatlonely'
        print('construct base')

    def sayHello(self):
        print('hello {0}'.format(self.name))

class Derive(Base):
    def __init__(self):
        Base.__init__(self)
        print('construct derive')
```

## 异常

```python
def div(x, y):
    if y == 0:
        raise ZeroDivisionError('ZeroDivisionError: x={0}, y={1}'.format(x, y))
    return x / y

try:
    div(2, 0)
except Exception as e:
    print(e)
```
