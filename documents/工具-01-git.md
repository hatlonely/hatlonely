# Git

分布式版本控制系统

## 安装

Mac自带git命令
Centos下执行 `sudo yum install git` 安装

## 全局配置

以下配置会写入 ~/.gitconfig文件中

```
git config --global user.name hatlonely
git config --global user.email hatlonely@gmail.com

git config --global core.editor vim
git config --global merge.tool vimdiff

git config --list
```

## 基本用法

从远端服务器下载服务到本地

```
git clone git@github.com:hatlonely/hatlonely.git
```

添加文件

```
git add README.md
```

提交文件到本地

```
git commit -m "add README.md"
```

同步本地代码到服务器（master为主干）

```
git push origin master
```

更新代码到本地

```
git pull -a
```

放弃更改 `git checkout <path>`

```
git checkout README.md
git checkout .
```

放弃添加

```
git reset README.md
git reset .
```

## 版本

列出所有的版本

```
git tag
git tag -l
```

创建版本 `git tag <tag_name>`

```
git tag v1.0.0.0
```

切换到特定版本 `git checkout <tag_name>`

```
git checkout v1.0.0.0
```

删除指定版本

```
git tag -d <tag_name>
```

同步本地版本到服务器 `git push origin <tag_name>`

```
git push origin v1.0.0.0
git push origin --tags
```

## 分支

列出所有分支，-r查看远端的分支，-a查看所有的分支

```
git branch
git branch -r
git branch -a
```

创建本地分支，`git branch <new_branch>`

```
git branch hatlonely
```

切换分支

```
git checkout hatlonely
```

合并分支

```
git checkout master
git merge hatlonely
```

重命名分支

```
git branch -m old_branch new_branch
```

删除分支，-r删除远端的分支

```
git branch -d hatlonely
git branch -d -r hatlonely
```

## github

世界上最大的代码托管平台，免费的git服务器，没用过github都不好意思说自己是程序员……

1. 创建github账号

    <https://github.com/>

2. 创建ssh-keys

    ```
    ssh-keygen -t rsa
    ```

3. 添加ssh-key到github账号

    复制`~/.ssh/id_rsa.pub`到`https://github.com/settings/keys` -> `New SSH key`

## 问题解决

`git status` 显示中文乱码

```
git config --global core.quotepath false
```

`git status` 彩色显示

```
git config --global color.ui true
```

