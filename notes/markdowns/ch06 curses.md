# 第六章 curses

第五章介绍的内容许多使用大量的底层代码，但大多数的应用程序需要更高层的接口，我们希望能够简单地绘制屏幕，并能用一组函数自动处理与终端相关的问题。

使用 curses 函数库可以达到这个目的。

延伸阅读：http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/index.html

---

## 用 curses 函数库进行编译

在我的 CentOS7 机器上，需要安装 curses 函数库，编程时，需引入头文件 curses.h ，并链接库 -lncurses 。

安装的命令是：

```bash
$ sudo yum install ncurses-devel.x86_64
```

书中对此进行了详细的讨论。

## curses 术语和概念

curses 例程工作在屏幕、窗口和子窗口之上。屏幕通常是指终端屏幕，它是设备上全部的可用显示面积。例程总是有一个标准窗口，即 stdscr ，它与物理屏幕尺寸完全一样。

可以创建其他窗口、子窗口，这些窗口相互重叠。

在 curses 程序中输出字符的过程是：

1. 使用 curses 函数刷新逻辑屏幕

2. 要求 curse 用 refresh 函数来刷新物理屏幕

逻辑屏幕以左上角为起点，坐标为(0,0)，坐标格式是(y,x)，y是行，x是列。 LINES 代表屏幕的行数， COLS 代表屏幕的列数。

curses 函数库在使用时需要创建和删除一些临时的数据结构，也就是在程序的开始调用 initscr 函数，在程序结束的时候调用 endwin 函数。 

!!!note
    - curses 没有定义层级关系，哪个窗口后绘制，它就会覆盖掉前面的内容。
    - curses 程序在结束后，原先显示的内容就被关掉，所以测试例程往往会 sleep 若干秒，以查看结果。
    - 如果在程序结束的时候，未调用 enwin 函数，在我的机器上就会出现终端的显示异常，这时候可以输入 stty sane 解决。

## 屏幕

所有的 curses 程序必须以 initscr 函数开始，以 endwin 函数结束。

initscr 返回指向 stdscr 结构的指针，如果失败就输出一条诊断错误信息并使程序退出。

### 输出到屏幕

curses 提供了一些用户刷新屏幕的基本函数：

- addch 输出字符
- addchstr 输出字符串
- printw 格式化输出字符串
- refresh 刷新 stdscr
- box 输出一个 box
- insch 插入字符
- insertln 插入行
- delch 删除字符
- deleteln 删除行
- beep 蜂鸣
- flash 闪烁

### 从屏幕读取

这些功能并不常用（不是从输入流读取）：

- inch 返回光标位置的字符及其属性
- instr innstr 将返回内容写入字符数组

### 清除屏幕

- erase 在每个屏幕的位置写上空白字符
- clear 清屏
- clrtobot 清除当前光标位置到屏幕结尾的所有内容
- clrtoeol 清除当前光标位置直到光标所处行行尾的所有内容。

### 移动光标

- move 可以移动光标（逻辑屏幕）

### 字符属性

每个字符都可以有一些属性控制在屏幕上的显示方式。预定义的属性有 A_BLINK A_BOLD A_DIM A_REVERSE A_STANDOUT 等。

使用下面的方法可以设置属性：

- attron 打开某个属性
- attroff 关闭某个属性
- attrset 设置属性

## 键盘

### 键盘模式

设置键盘模式的函数有：

- echo 设置回显
- noecho 设置不回显
- cbreak 表示输入字符后立即传送给程序
- nocbreak 表示输入字符后要等待回车键才传送数据给程序

### 键盘输入

- getch 读取一个字符
- getstr getnstr 读取一个字符串
- scanw 读取格式化的字符串

## 窗口

可以在物理屏幕上同时显示多个不同尺寸的窗口。并且输入输出的函数有着更通用的接口，来应对不同的窗口。

### WINDOW 结构

标准屏幕 stdscr 只是 WINDOW 结构的一个特例。可以使用 newwin 和 delwin 来创建和销毁一个窗口。但不要删除标准窗口。

### 通用函数

对诸如 addch printw 加上一些前缀即变成了通用的函数，前缀 w 用于窗口， mv 用于光标移动， mvw 用于在窗口中移动光标。

如果加了 w 前缀，那么函数就需要第一个参数 WINDOW 指针。如果是 mv 前缀，那么就需要一个 y,x 坐标表示光标移动到的位置。如果是 wmv 那么就需要 (WINDOW*, Y, X) 这样的额外参数。

### 移动和更新窗口

下面的函数可以移动和重新绘制窗口：

- mvwin 移动窗口
- wrefresh 刷新窗口
- wclear 清窗口内容
- werase erase 窗口内容
- touchwin 告知窗口发生了改变，从而可以重新 refresh ，即使没有改变
- scrollok 设置可否卷屏
- scroll 向上卷屏一行

### 优化屏幕刷新

在慢速链路上，屏幕绘制的速度可能会慢得让人难以忍受。 curses 为此提供了一种特殊手段，用到这样的函数：

- wnoutrefresh
- doupdate

wnoutrefresh 用于决定把哪些字符发送到屏幕上，但它不真正发送这些字符，真正将更新发送到终端的工作由 doupdate 来完成。

如果只是调用 wnoutrefresh ，然后立即调用 doupdate ，则它的效果与直接调用 wrefresh 完全一样。但如果想重新绘制多个窗口，你可以为每个窗口分别只调用 wnoutrefresh ,然后只需要在调用最后一个 wnoutrefresh 之后调用一次 doupdate 函数即可。

这允许 curses 依次为每个窗口执行屏幕更新计算工作，最后仅把最终的更新结果输出到屏幕上。这种做法可以最大限度地减少 curses 需要发送的字符数目。

## 子窗口

使用 subwin 函数创建子窗口， delwin 函数删除子窗口。

子窗口的用法几乎与普通窗口一样。只不过子窗口与父窗口共享着字符存储。

## keypad 模式

一般键盘至少都会包含方向键和功能键。

对于大多数终端来说，解码这些按键是一件困难的事情，因为它们往往会发送以 escape 字符开头的字符串序列。

curses 通过一组以 `KEY_` 为前缀的定义来管理功能逻辑键。

curses 在启动时会关闭转义序列与逻辑键之间的转换功能，该功能需要通过调用 keypad 函数来启用。

在 keypad 模式中，读键盘操作不仅能够返回用户按下的键，还将返回与逻辑按键对应的 `KEY_` 定义。

## 彩色显示

curses 为每个字符定义一个前景色和背景色，称之为颜色组合（ color pair ）。

在使用 curses 函数库的颜色功能之前，必须使用 has_colors 函数检查终端是否支持彩色显示功能，然后使用 start_color 函数对程序进行初始化。

一旦 start_color 函数被成功调用，变量 COLOR_PAIRS 将被设置为终端所能支持的颜色组合数目的最大值，变量 COLORS 定义可用颜色数目的最大值。

每种颜色以一个从0到63的数字作为其唯一的 ID 号。

把颜色作为属性使用之前，必须先调用 init_pair 函数对准备使用的颜色组合进行初始化，然后使用 COLOR_PAIR 函数生成一个属性，最后用 attrset 函数设置这个属性。

curses 定义了一些基本颜色，名字以 `COLOR_` 为前缀。

## pad

在编写更高级的程序时，有时候需要先建立一个逻辑屏幕，然后再把它的全部内容或部分内容输出到物理屏幕上。

pad 就是用于此目的。它通常被创建到屏幕的外面。在合适的时机再把其部分内容刷新到屏幕上。

使用 newpad 函数创建一个 pad ，它也是一个 WINDOW 指针。

使用 prefresh 函数刷新 pad 。