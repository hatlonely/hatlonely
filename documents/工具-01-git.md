# git

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

## 版本控制tag

查看所有的版本

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

## 



