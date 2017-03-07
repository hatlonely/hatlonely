# 编码规范

## google 编码规范

<http://zh-google-styleguide.readthedocs.io/en/latest/google-python-styleguide/python_language_rules/>

## 风格规范

1. 只是用空格缩进，缩进为4个空格
2. 一元运算符后无空格；二元运算符前后均有空格；逗号、分号、冒号前面不空格，后面空格
3. 行尾永远不加分号
4. 条件永远不加括号
5. 避免连续的空行
6. 字符串使用单引号，多行字符串使用三重双引号
7. 使用隐式False

    ```python
    if len(seq) == 0:   # 避免
        pass

    if seq:             # 推荐
        pass
    ```

## 命名规范

1. 文件命名，全小写加下划线(module_name)
2. 类名，首字母大写驼峰命名(ClassName)
3. 函数名，全小写加下划线(function)
4. 类方法，全小写加下划线(method_name)
5. 普通变量，全小写加下划线(local_variable)

    ```python
    #!/usr/bin/env python3
    # hello_world.py

    class HelloWorld(object):
        def say_hello(name):
            print('hello {}'.format(name))

    def say_hello(name):
        hello_world = HelloWorld()
        hello_world.say_hello(name)

    def main():
        say_hello('hatlonely')

    if __name__ == '__main__':
        main()
    ```

## 语法规范

1. 使用as捕获异常，而不是用逗号

    ```python
    try:
        raise Error
    except Error as error:
        pass
    ```

2. 使用in来判断容器是否包含某个元素

    ```python
    for key in adict:
        pass

    if key in adict:
        pass
    ```

3. 简单条件使用选择表达式

    ```python
    name = 'hatlonely' if age < 30 else 'sonic'
    ```

## 注释规范

1. 方法注释

    ```python
    def fetch_bigtable_rows(big_table, keys, other_silly_variable=None):
        """Fetches rows from a Bigtable.

        Retrieves rows pertaining to the given keys from the Table instance
        represented by big_table.  Silly things may happen if
        other_silly_variable is not None.

        Args:
            big_table: An open Bigtable Table instance.
            keys: A sequence of strings representing the key of each table row
                to fetch.
            other_silly_variable: Another optional variable, that has a much
                longer name than the other args, and which does nothing.

        Returns:
            A dict mapping keys to the corresponding table row data
            fetched. Each row is represented as a tuple of strings. For
            example:

            {'Serak': ('Rigel VII', 'Preparer'),
             'Zim': ('Irk', 'Invader'),
             'Lrrr': ('Omicron Persei 8', 'Emperor')}

            If a key from the keys argument is missing from the dictionary,
            then that row was not found in the table.

        Raises:
            IOError: An error occurred accessing the bigtable.Table object.
        """
        pass
    ```

2. 类注释

    ```python
    class SampleClass(object):
        """Summary of class here.

        Longer class information....
        Longer class information....

        Attributes:
            likes_spam: A boolean indicating if we like SPAM or not.
            eggs: An integer count of the eggs we have laid.
        """

        def __init__(self, likes_spam=False):
            """Inits SampleClass with blah."""
            self.likes_spam = likes_spam
            self.eggs = 0

        def public_method(self):
            """Performs operation blah."""
    ```



