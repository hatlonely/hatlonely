# xcode 插件安装

## 安装插件管理功率 Alcatraz

github地址： <https://github.com/alcatraz/Alcatraz>

输入如下命令安装：

```
curl -fsSL https://raw.github.com/alcatraz/Alcatraz/master/Scripts/install.sh | sh
```

问题

```
xcrun: error: unable to find utility "xcodebuild", not a developer tool or in PATH
```

解决

```
sudo xcode-select -s /Applications/Xcode.app/Contents/Developer
```

## 卸载

Xcode 8 不支持 Alcatraz，所以卸载了。。。

```
# 卸载 Alcatraz 插件
rm -rf ~/Library/Application\ Support/Developer/Shared/Xcode/Plug-ins/Alcatraz.xcplugin

# 卸载所有插件
rm -rf ~/Library/Application\ Support/Alcatraz/
```
