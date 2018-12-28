# 第十六章 用GTK+进行GNOME编程

Linux 中所有的 GUI 库都基于被称作X视窗系统的底层视窗系统。

在编写本章节的代码时，需要安装好相应的库，在 CentOS7 上，使用这个脚本安装：

[install_libs](../codes/ch16_用GTK+进行GNOME编程/install_libs.sh)

---

## X视窗系统简介

X是一个开源的图形化系统。X没有定义用户界面，但提供了创建用户界面的手段。这意味这可以自由地创建自己的整个桌面环境。

两个桌面项目逐渐浮现成为了 Linux 用户的最爱： GNOME 和 KDE 。

X视窗系统被分别称为硬件级和应用程序级组件，它们分别被称为X服务器和X客户端。这些组件使用X协议进行通信。

### X服务器

X服务器运行在用户的本地机器上，它在屏幕上完成低层的绘图操作。X服务器直接与显卡交互。

X服务器通过鼠标和键盘监听用户输入，并将键盘按键和鼠标点击传输给X客户端应用程序。这些信息被称为事件（ event ）。

### X客户端

X客户端是以X视窗系统作为 GUI 的任何程序。例如 xterm 。通常情况下，X客户端等候X服务器传送用户事件，然后通过给X服务器发送重绘消息来响应，

### X协议

X客户端和X服务器使用X协议进行通信，这使得客户端和服务器可以通过网络分离。对于绝大多数个人 Linux 系统来说，X客户端和X服务器都运行在同一个系统上。

### Xlib库

Xlib 库是X客户端间接用于产生X协议消息的库。它提供一个非常底层的 API 供客户端在X服务器上绘制非常基本的元素，并响应最简单的输入。

GUI程序员应该使用X工具包，这比使用 Xlib 要简单方便。

### X工具包

是一个GUI库，X客户端可以利用它来极大地简化窗口、菜单和按钮等的创建。诸如此类的 GUI 元素被称为 widget 。

最流行的工具包现在是 GTK+ 和 QT 。它们分别构成了 GNOME 和 KDE 桌面的基础。

### 窗口管理器

窗口管理器负责定位屏幕上的窗口。它还负责装饰每个窗口，通常由一个框架和一个带有最大化、最小化和关闭图标的标题栏组成。

### 创建GUI的其他方法——平台无关的窗口API

比如使用 JAVA， C#， PYTHON 等。

## GTK+简介

GTK+是一个函数库，它提供了一组已经制作好的组件。

GTK+完全是用C语言编写的，而且绝大多数GTK+软件也是用C语言编写的。许多语言绑定使你可以在其他语言中使用GTK+ ，比如 C++ ， Python ， PHP 等。

### GLib 类型系统

GTK+ 中，有许多以字母g开头的C语言数据类型，如 gint, gchar, gshort 。这是为了跨平台开发。

GLib 和 GObject 提供了一组数据类型、函数和宏的标准替代集来进行内存管理和处理常见任务，从而实现跨平台开发。

- gint, guint, gchar, guchar, glong, gulong, gfloat, gdouble 是标准C语言数据类型的简单替代

- gpointer 与 (void\*) 同义。

- gboolean 用于表示布尔类型的值。可以取值 TRUE 和 FALSE 。

- gint8, guint8, gint16, guint16, gint32, guint32 是保证字节长度的类型。

### GTK+对象系统

尽管 GTK+ 是完全用C语言编写的，但是它通过 GObject 库支持对象和面向对象编程。这个库通过宏来支持对象继承和多态。

为了方便，所有 Widget 的创建函数都返回一个GtkWidget 的类型。例如：

```c
GtkWdiget* gtk_window_new(GtkWindowType type);
```

可以通过专用的宏实现继承关系间的类型转化：

```c
// 把 GtkWidget* 转化成了一个 GtkContainer*
gtk_container_add(GTK_CONTAINER(window), awidget);
```

### GNOME 简介

GNOME 的目的是为 Linux 创建一个统一的桌面。

现在它已经成为 Fedora, Red Hat, Ubuntu 以及 openSUSE 等发行版默认 Linux 桌面的基础。

### 安装 GNOME/GTK+ 开发库

书中介绍了一些方法。

在我使用的 CentOS7 下面，使用这样的命令安装：

```bash
$ sudo yum -y install gtk2.x86_64
$ sudo yum -y install gtk2-devel.x86_64
$ sudo yum -y install gtk2-engines.x86_64
$ sudo yum -y install libgnome.x86_64
$ sudo yum -y install libgnome-devel.x86_64
$ sudo yum -y install libgnomeui.x86_64
$ sudo yum -y install libgnomeui-devel.x86_64
```

可以运行 GTK+ 的演示程序，它还包含了代码：

```bash
$ gtk-demo
```

使用这样的命令来生成编译选项构建 gtk+ 程序：

```bash
`pkg-config --cflags --libs gtk+-2.0`
```

[gtk_window_new](../codes/lab/api/GTK2.0/window.c) 可以创建一个窗口。

一个 gtk 程序的简单框架是：

```c
#include <gtk/gtk.h>

static Widget *window;

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);	// 初始化 GTK+ 库，必须在调用任何 GTK 函数之前调用

	// 给窗口添加内容

	gtk_widget_show_all(window); // 显示实际窗口和其内容
	gtk_main(); // 把控制权交给 GTK+ 来启动交互过程，并且一直运行，直到调用 gtk_main_quit 才返回
    return 0;
}
```

## 事件、信号和回调函数

所有的 GUI 库都有一个共同点：必须存在某种机制来响应用户动作并执行相应代码。

现代窗口系统用事件和事件监听系统来处理这个问题。其思想是，每次用户输入都触发一个事件。程序员需要编写监听这些事件的代码，以及当事件被触发时要执行的代码。

GTK+ 有自己的事件和监听器系统，它们被称为信号和回调函数。

回调函数的原型如：

```c
void a_callback(GtkWidget *widget, gpointer user_data);
```

连接回调函数的方法是 [g_signal_connect](../codes/lab/api/GTK2.0/g_signal_connect.c) 。

## 组装盒构件

GUI 的布局对其可以用性来说至关重要。排列构件的真正困难在于，你不能指望所有用户都有相同的屏幕分辨率，或者有相同的窗口大小、主题、字体、颜色方案。

为了保持一致，要避免使用绝对坐标来放置构件，而是采用一种更灵活的布局系统。 GTK+ 通过容器构件来实现这一目标。盒构件是一个非常有用的容器构件类型。

盒是一个不可见的构件，其工作就是包含其他的构件，并控制它们的布局。

使用 gtk_hbox_new 和 gtk_vbox_new 来创建一个横向和纵向的盒构件。

使用 gtk_box_pack_start 或 gtk_box_pack_end 来向盒构件添加构件。

[参考代码](../codes/lab/api/GTK2.0/box.c)

## Gtk+构件

本节介绍了 [GtkWindow](../codes/lab/api/GTK2.0/window2.c), [GtkEntry](../codes/lab/api/GTK2.0/entry.c), [GtkSpinButton](../codes/lab/api/GTK2.0/spinbutton.c), [GtkButton](../codes/lab/api/GTK2.0/button.c), [GtkCheckButton](../codes/lab/api/GTK2.0/check_button.c), [GtkToggleButton](../codes/lab/api/GTK2.0/toggle_button.c), [GtkRadioButton](../codes/lab/api/GTK2.0/radio_button.c), [GtkTreeView](../codes/lab/api/GTK2.0/tree_view.c) 的相关 API 。

## GNOME 构件

GTK+ 被设计成独立于桌面的。它不假定运行在 GNOME 中，甚至不假定它运行在 Linux 上。这样， GTK+ 可以被相对容易地移植到 Windows 或者任何其他视窗系统中。但其导致的结果是： GTK+ 缺乏将程序与桌面紧密结合的方法。

GNOME 库包含 GNOME 构件，它们扩展了 GTK+ ，用一些更容易使用的构件替换了 GTK+ 中的部分构件。

略去后续繁杂的内容。