# CentOS7 软件安装

一些 windows 下常用的软件，或许可以使用 AppImage 来使用，比如钉钉。

见：https://appimage.org/

使用 Settings -> Detailes 来修改默认使用的程序。

---

## lantern - VPN

安装：

```bash
$ sudo yum install epel-release
$ sudo yum install alien.noarch
$ sudo yum install rpmrebuild
$ sudo yum install libappindicator-gtk3
```

下载 lantern Ubuntu 64 位包：https://github.com/getlantern/lantern/releases/tag/latest

转化成 rpm 包：

```bash
$ sudo alien -r lantern-installer-64-bit.deb
```

修改 rpm 包：

```bash
$ sudo rpmrebuild -pe lantern-???.x86_64.rpm
```

替换内容：

```
(Converted from a deb package by alien version 8.95.)
%files
#%dir %attr(0755, root, root) "/"
#%dir %attr(0755, root, root) "/usr"
#%dir %attr(0755, root, root) "/usr/bin"
%attr(0777, root, root) "/usr/bin/lantern"
#%dir %attr(0755, root, root) "/usr/lib"
%dir %attr(0755, root, root) "/usr/lib/lantern"
%attr(0644, root, root) "/usr/lib/lantern/.packaged-lantern.yaml"
%attr(0644, root, root) "/usr/lib/lantern/lantern-binary"
%attr(0755, root, root) "/usr/lib/lantern/lantern.sh"
%attr(0644, root, root) "/usr/lib/lantern/lantern.yaml"
#%dir %attr(0755, root, root) "/usr/share"
#%dir %attr(0755, root, root) "/usr/share/applications"
%attr(0644, root, root) "/usr/share/applications/lantern.desktop"
#%dir %attr(0755, root, root) "/usr/share/doc"
%dir %attr(0755, root, root) "/usr/share/doc/lantern"
%doc %attr(0644, root, root) "/usr/share/doc/lantern/changelog.gz"
%doc %attr(0644, root, root) "/usr/share/doc/lantern/copyright"
#%dir %attr(0755, root, root) "/usr/share/icons"
#%dir %attr(0755, root, root) "/usr/share/icons/hicolor"
#%dir %attr(0755, root, root) "/usr/share/icons/hicolor/128x128"
#%dir %attr(0755, root, root) "/usr/share/icons/hicolor/128x128/apps"
%attr(0644, root, root) "/usr/share/icons/hicolor/128x128/apps/lantern.png"
%changelog
```

按照最后输出的目录安装：

```bash
sudo rpm -i ???.rpm
```

运行 lantern 即可。

## vscode - 代码、文档编辑器

```bash
$ sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc
$ sudo sh -c 'echo -e "[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc" > /etc/yum.repos.d/vscode.repo'
$ yum check-update
$ sudo yum install code
```

## Chrome - 谷歌浏览器

安装:

- 添加源文件 /etc/yum.repos.d/google-chrome.repo，填写内容：

```
[google-chrome]
name=google-chrome
baseurl=http://dl.google.com/linux/chrome/rpm/stable/x86_64
enabled=1
gpgcheck=1
gpgkey=https://dl.google.com/linux/linux_signing_key.pub
```

- yum install google-chrome-stable

## flash-player - 浏览器视频播放插件

进入 Adobe Flash Player 官网 https://get.adobe.com/cn/flashplayer/

选择 .rpm 适用于 linux

下载完毕后，打开命令行，输入：

```shell
sudo rpm -ivh flash-player-npapi-31.0.0.153-release.x86_64.rpm
```

重启浏览器。

## Filezilla - FTP 工具

安装

```bash
yum -y install epel-release
yum -y install filezilla
```

安装完毕后，直接搜索并运行。

**使用 ssh key 登陆的方法**

1. In FileZilla->Settings.. select Connection->SFTP
2. Press the Add key file... button
3. 选择一个可以用的 private key
4. 会提示转换文件格式，并保存到一个位置，跟着做
5. 点击 OK
6. Choose Protocol "SFTP" and select Logon Type "Normal". Don't worry about a password if you key file doesn't have a password
7. Click Connect and you'll see your files

## VirtualBox - 虚拟机

安装

```bash
$ cd /etc/yum.repos.d
$ wget http://download.virtualbox.org/virtualbox/rpm/rhel/virtualbox.repo
$ sudo yum install VirtualBox-5.2.x86_64
```

安装完毕后，直接搜索并运行。

参考：https://wiki.centos.org/zh/HowTos/Virtualization/VirtualBox

## VLC - 视频播放器

安装

```bash
su -
yum install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
yum install https://download1.rpmfusion.org/free/el/rpmfusion-free-release-7.noarch.rpm
yum install vlc
```

参考：https://www.videolan.org/vlc/download-redhat.html

## steam - 游戏平台

安装

```bash
sudo yum install steam.i686
```

启动

```bash
$ LD_PRELOAD='/usr/$LIB/libstdc++.so.6' LIBGL_DRI3_DISABLE=1 steam
```

## KDevelop - C++ IDE

安装并启动：

```bash
wget -O KDevelop.AppImage https://download.kde.org/stable/kdevelop/5.3.0/bin/linux/KDevelop-5.3.0-x86_64.AppImage
chmod +x KDevelop.AppImage
./KDevelop.AppImage
```

参考：https://www.kdevelop.org/download

## Mysql Workbench - Mysql 图形化工具

安装：

1. 安装 mysql 源， rpm 下载地址：https://dev.mysql.com/downloads/repo/yum/

2. 安装：yum install mysql-workbench-community.x86_64

## TeamViewer - 远程桌面

先引入 key ：

```
$ wget https://dl.tvcdn.de/download/linux/signature/TeamViewer2017.asc
$ sudo rpm --import TeamViewer2017.asc
```

使用 yum 安装：

```
$ wget https://download.teamviewer.com/download/linux/teamviewer.x86_64.rpm
# yum install epel-release
# yum install ./teamviewer*.rpm
```

参考：https://community.teamviewer.com/t5/Knowledge-Base/How-to-install-TeamViewer-on-Red-Hat-and-CentOS/ta-p/30708