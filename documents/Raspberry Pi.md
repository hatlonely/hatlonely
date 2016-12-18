# Raspberry Pi

## centos 安装

1. 从官网下载 centos 7 <http://mirror.centos.org/altarch/7/isos/armhfp/> 下载 CentOS-Userland-7-armv7hl-Minimal-1611-RaspberryPi3.img.xz
2. 解压centos 压缩文件得到 CentOS-Userland-7-armv7hl-Minimal-1611-RaspberryPi3.img
3. 下载 Win32DiskImager <pan.baidu.com/s/1bp2pZFx>
4. 使用 Win32DiskImager 制作磁盘映像到tf上
5. 将tf卡插入到树莓派中即可使用
6. 使用 `root` 连接到树莓派，密码 `centos`
7. 拓展 `／` 目录下的空间执行 `/usr/local/bin/rootfs-expand`

## samba 服务器配置

1. samba服务下载安装， `sudo yum install samba-client samba samba-common`
2. 关闭 selinux， `sudo setenforce 0`
3. 关闭防火墙，`sudo systemctl stop firewalld.service`
4. 启动 samba 服务， `sudo systemctl start smb nmb`
5. 添加 samba 用户，`sudo smbpasswd -a hatlonely`
