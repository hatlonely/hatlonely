## Sublime Text

## 官网链接

<http://www.sublimetext.com/3>

## 快捷键

|      快捷键       |       使用       |
|-------------------|------------------|
| `cmd + shift + l` | 选中区域多行编辑 |
| `cmd + shift + p` | 调出 console     |
| `cmd + x`         | 剪切当前行       |

## 配置文件

`Sublime Text` -> `Preferences` -> `Setting`

``` json
{
    "font_face": "Inconsolata",
    "font_size": 20,
    "translate_tabs_to_spaces": true
}
```

## 插件安装

### package control

package control 是一个插件安装管理软件
按如下步骤安装 package control

1. ctrl + ` 调出 console
2. 粘贴如下代码并回车

    ``` python
    import urllib.request,os; pf = 'Package Control.sublime-package'; ipp = sublime.installed_packages_path(); urllib.request.install_opener( urllib.request.build_opener( urllib.request.ProxyHandler()) ); open(os.path.join(ipp, pf), 'wb').write(urllib.request.urlopen( 'http://sublime.wbond.net/' + pf.replace(' ','%20')).read())
    ```

package control 使用

1. `cmd + shift + p` 调出命令版
2. 输入 install，选择 `Install Package` 选项
3. 从列表中选择需要安装的插件

### 前端插件

1. emmet
2. JsFormat
3. HTML-CSS-JS Prettify

### markdown 支持

markdown-editing/markdown preview/table editor/markdow extended

table editor 用法：首先需要用ctrl + shift + p打开这个能
```
Table Editor: Enable for current syntax 
Table Editor: Enable for current view 
Table Editor: Set table syntax ... for current view
```
然后就按tab来自动完成

