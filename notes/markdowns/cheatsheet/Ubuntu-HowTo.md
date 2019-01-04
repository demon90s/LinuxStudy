# Ubuntu HowTo

version: 18.04

---

## su -

Ubuntu的默认root密码是随机的，即每次开机都有一个新的root密码。我们可以在终端输入命令 sudo passwd，然后输入当前用户的密码，enter，终端会提示我们输入新的密码并确认，此时的密码就是root新密码。修改成功后，输入命令 su - ，再输入新的密码就ok了。

## 添加中文拼音输入法

打开 Language Support ，按照提示更新好，重启。然后打开 Settings -> Region & Language , 在 Input Source 下加一个 Chinese(Intelligent Pinyin)。

## sh 命令执行问题

默认 sh 链接到了 dash ，而工作和学习中通常使用 bash ，所以就先把此链接删掉，重新构造软链接。

## 使用 fbterm 解决 tty 中文无法显示/输入问题

默认情况下，tty 下面的中文都是无法显示的格子，这时候需要用 fbterm 来解决。

安装：

sudo apt install fbterm

给非 root 用户增加执行权限（你需要执行以下命令将非root用户添加到video用户组中:）：

```
sudo gpasswd -a YOUR_USERNAME video
sudo chmod u+s /usr/bin/fbterm
```

进入 tty 后，输入 fbterm 即可。

修改 ~/.fbtermrc 文件可以修改配置。

在 fbterm 环境下，使用 alt + fN 来切换终端，而不是 ctrl + alt + fN

还可以在 .profile 下面追加脚本，使得登入终端后自动进入 fbterm

```bash
# auto turn to fbterm
if [ "$TERM" = linux ]; then
        for t in 3 2 1
        do
                tput reset
                echo "Turning to fbterm in $t seconds..."
                sleep 1
        done

        fbterm
fi
```

若要使用中文拼音输入，则：

sudo apt-get install fcitx-frontend-fbterm

然后在 Settings -> Region & Language -> Manage Installed Languages 里面将 keyboard Input method system 修改成 fcitx 。

之后，修改 .fbtermrc 的配置项目为：input-method=fcitx-fbterm

重启后，进入终端，键入 ctrl + space ，即可开启切换中文拼音输入法。

## 安装一些软件

主要使用 apt-get 命令安装。

### svn

sudo apt-get install subversion

### vim

sudo apt-get install vim

### filezilla

sudo apt-get install filezilla

### git

sudo apt-get install git

### cmake 2.8

通过源码安装：https://www.biostars.org/p/195484/

### mysql or mariadb

sudo apt-get install mariadb-server mariadb-client

启动：/usr/bin/mysqld_safe --datadir='/var/lib/mysql'

### rapidsvn

sudo apt-get install rapidsvn
sudo apt-get install meld

show diff:

菜单栏 -> View -> Preferences， 设置 Diff Tool 为 meld

meld 查看/设置支持的编码：

```
gsettings get org.gnome.meld detect-encodings
gsettings set org.gnome.meld detect-encodings "['utf8','latin1', 'GBK']"
```