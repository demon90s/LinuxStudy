# 第十七章 用Qt进行KDE编程

Qt 是用 C++ 语言编写的， C++ 也是编写 QT/KDE 程序的标准语言。

---

## KDE 和 Qt 简介

KDE （K桌面环境）是一个基于 QT GUI 库的开源桌面环境。 KDE 中包含了大量的应用程序和工具。

QT 是一个用 C++ 编写的、成熟的、跨平台的 GUI 工具包。其开发公司为自由软件社区提供了一个免费的版本。

## 安装 QT

书本使用的版本是 QT3 ，这在 CentOS7 上可以这样安装：

```bash
sudo yum -y install qt3
sudo yum -y install qt3-devel
```

如果是使用 Ubuntu 18.04 ，那么我安装的方法是：

先下载一个源码包（qt-x11-free_3.3.8-b.orig.tar.gz）：https://download.qt.io/archive/qt/3/

然后：

```
su -
cd /usr/local
tar zxvf qt-x11-free_3.3.8-b.orig.tar.gz
cd qt-x11-free-3.3.8b/
./configure
make
```

编译好后，把目录名字改一下：

```
cd ..
mv qt-x11-free-3.3.8b/ qt-3.3
```

然后设置程序的头文件目录以及链接目录和链接库。

其余的方式见书本。

编译程序的时候，需要引入 qt 的头文件目录，和链接 qt 库：

```
# 书中的例子
$ g++ -o qt1 qt1.cpp -I$QTDIR/include -L$QTDIR/lib -lqui
```

## 信号和槽

信号和信号处理是 GUI 应用程序用来响应用户的主要机制。 QT 的信号处理机制由信号（ signal ）和槽（ slot ）构成。

QT 定义了两个伪关键字（ signal 和 slot ）来标识代码中类的信号和槽。这意味着代码必须经过一个单独的预-预处理阶段（ pre-pre processing ），来搜索这些伪关键字并用额外的C++代码对它们进行替换。

信号和槽还有一些使用限制，但不是很严重：

- 信号和槽必须是 QObject 的派生类的成员函数

- 如果使用多重继承， QObject 必须在类列表的第一个出现

- 在类声明中必须出现 Q_OBJECT 语句

- 信号不能在模板中使用

- 函数指针不能用作信号和槽的参数

- 信号和槽不能被覆写和提升为公共方法

通过 QObject::connect 方法将信号连接到槽。

QLayout 提供了排列构件和布局的方法。其子类 QVBoxLayout 和 QHBoxLayout 分别以垂直和水平的方向包含其他构件和布局。

使用 QBoxLayout::addWidget 和 QBoxLayout::addLayout 完成这个功能。
