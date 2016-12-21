# github入门

## git多人协作

```
$ git clone git@github.com:hatlonely/helloword.git  # 下载
$ vi helloworld.cpp         # 修改
$ git pull -a               # 更新合并
$ git status                # 查看状态
$ git add helloworld.cpp    # 提交所有修改
$ git commit -m "message"   # 提交
$ git push origin master    # 上传
```

## git个人文档管理

1. 配置name和email

    ```
    $ git config --global user.email "hatlonely@gmail.com"
    $ git config --global user.name "hatlonely"
    ```

2. 创建一个本地目录

    ```
    $ cd $WORK
    $ mkdir git_workspace
    $ cd git_workspace
    $ mkdir heloworld
    $ cd helloworld
    $ touch helloworld.cpp
    ```

3. 本地文件添加到git的管理中

    ```
    $ git init
    $ git add helloworld.cpp
    $ git commit -m "add helloworld.cpp"
    ```

## ssh配置

1. $ `ssh-keygen -t rsa -C "hatlonely@gmail.com"` => 在`~/.ssh`文件夹中产生`id_rsa.pub`和`id_rsa`
2. 在网页上登录：<https://github.com/>，`Edit Your Profile` -> `SSH Keys` -> `Add SSH key`
3. 复制1中`id_rsa.pub`总的内容到Key中

## 其他

重命名

```
$ git mv oldname newname
$ git add newname
$ git commit -m "rename oldname newname"
$ git push origin master
```

不小心提交了不必要的文件（git commit之前的add操作）重置

```
$ git reset
```

## 参考

- [github官网](https://github.com/)
