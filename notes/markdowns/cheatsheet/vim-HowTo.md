# vim HowTo

## 设定与.vimrc

.vimrc example:

```
set nu
set encoding=utf-8 fileencodings=ucs-bom,utf-8,cp936
set nobackup
set autoindent
set tabstop=4
```

设定:

|设定|说明|
|:-:|:-:|
|:set nu|显示行号|
|:set nonu|不显示行号|
|:set list|显示不可见字符|
|:set nolist|不显示不可见字符|
|:set path+=dir|添加dir为find命令的搜索路径|

## 缓冲区

:ls 命令列出已经打开的文件

:bN 命令选择打开的文件, N是编号

:bdelete N1 N2 删除编号为N1 N2的缓冲区

## 文本编辑

核心在于明确操作单元.

### 移动光标

字符:

h - 左移一个字符
l - 右移一个字符

单词:

w - 移动到下一个单词的开头
b - 移动到前一个单词的开头

行:

j - 下移一行
k - 上移一行
0 - 移动到行开头
$ - 移动到行末尾
:n - 移动到第n行

屏:

H - 屏幕开头
M - 屏幕中间
L - 屏幕末尾

页:

ctrl + E - 向下滚动一行
ctrl + Y - 向上滚动一行
ctrl + F - 向下滚动一页
ctrl + B - 向上滚动一页

### 其他命令

ctrl + g 显示文件名

## 在左侧打开文件浏览器

:Vex

在文件浏览器窗口键入i切换浏览方式.

键入Enter展开目录.

键入-跳到上一级目录.

## 窗口

修改垂直窗口大小, 减少20个char::

:vertical resize -20

## 临时退出vim回到 shell

:sh

$ exit # 返回 vim

:qa # 关闭掉所有打开的窗口

## 执行外部命令

`:! <cmd>`

显示命令历史, 可以从历史中选择

`q:`
