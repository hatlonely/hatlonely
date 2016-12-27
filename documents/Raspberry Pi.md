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

1. samba服务下载安装

    ```
    sudo yum install samba-client samba samba-common
    ```

2. 关闭 selinux

    ```
    sudo setenforce 0
    ```

3. 关闭防火墙

    ```
    sudo systemctl stop firewalld.service
    ```

4. 启动 samba 服务

    ```
    sudo systemctl start smb nmb
    ```

5. 添加 samba 用户

    ```
    sudo smbpasswd -a hatlonely
    ```

## centos 免密码登陆

1. 客户机生成公钥文件，`ssh-keygen`
2. 服务器添加信任关系，将客户机上的 `~/.ssh/id_rsa.pub` 复制到服务器上的 ~/.ssh/authorized_keys 中，可以在客户机上执行如下命令

    ```
    cat ~/.ssh/id_rsa.pub | ssh 192.168.0.106 "cat - >> ~/.ssh/authorized_keys
    ```

3. 修改服务器sshd配置文件

    ```
    RSAAuthentication yes
    PubkeyAuthentication yes
    AuthorizedKeysFile  .ssh/authorized_keys
    PasswordAuthentication no   # 关闭密码认证
    ```

4. 服务器重启 sshd 服务

    ```
    systemctl restart sshd.service
    ```

## 无线网络设置

1. 安装wifi模块

    ```
    sudo curl --location https://github.com/RPi-Distro/firmware-nonfree/raw/54bab3d6a6d43239c71d26464e6e10e5067ffea7/brcm80211/brcm/brcmfmac43430-sdio.bin > /usr/lib/firmware/brcm/brcmfmac43430-sdio.bin

    sudo curl --location https://github.com/RPi-Distro/firmware-nonfree/raw/54bab3d6a6d43239c71d26464e6e10e5067ffea7/brcm80211/brcm/brcmfmac43430-sdio.txt > /usr/lib/firmware/brcm/brcmfmac43430-sdio.txt
    ```

2. 查看无线网卡

    ```
    nmcli d
    nmcli d wifi
    sudo nmcli d wifi connect <ssid> password <password>
    ```

3. 设置静态ip

    ```
    sudo vi /etc/sysconfig/network-scripts/ifcfg-doraemon-<ssid>

    # add by hatlonely
    BOOTPROTO=static        # 静态IP
    IPADDR=192.168.1.101    # IP地址
    GATEWAY=192.168.1.1     # 默认网关
    NETMASK=255.255.255.0   # 子网掩码
    # end hatlonely
    ```

## 设置运行级别

1. inittab里面有修改运行级别的说明

    ```
    cat /etc/inittab
    ```

1. 查看当前的运行级别

    ```
    systemctl get-default
    ```

2. 设置运行级别

    ```
    sudo systemctl set-default multi-user.target
    ```




