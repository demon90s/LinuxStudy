# Linux程序设计

学习环境：CentOS 7

对于第五章和第六章使用了头 curses.h 和 term.h 中的功能，需要安装 curses 开发包：yum install ncurses-devel.x86_64，并在构建程序时加入链接选项 -lncurses

---

## 实验例程

### 第1章 入门

[第一个Linux C语言程序](./ch01_入门/hello.c)

### 第2章 shell程序设计

[变量的使用](./ch02_shell程序设计/var.sh)

### 第3章 文件操作

[另一个文件复制程序（块复制）](./ch03_文件操作/copy_block.c)

[一个文件复制程序](./ch03_文件操作/copy_system.c)

### 第4章 Linux环境

[getopt函数](./ch04_Linux环境/argopt.c)

[程序参数](./ch04_Linux环境/args.c)

[ctime函数](./ch04_Linux环境/ctime.c)

[getenv 和 putenv](./ch04_Linux环境/environ.c)

[time函数](./ch04_Linux环境/envtime.c)

[gmtime函数](./ch04_Linux环境/gmtime.c)

[主机信息](./ch04_Linux环境/hostget.c)

[资源限制](./ch04_Linux环境/limits.c)

[logmask](./ch04_Linux环境/logmask.c)

[getopt_long](./ch04_Linux环境/longopt.c)

[environ 变量](./ch04_Linux环境/showenv.c)

[strftime和strptime](./ch04_Linux环境/strftime.c)

[tmpnam和tmpfile](./ch04_Linux环境/tmpnam.c)

[用户信息](./ch04_Linux环境/user.c)

### 第5章 终端

[你自己的kbhit函数](./ch05_终端/kbhit.c)

[用C语言编写的菜单例程](./ch05_终端/menu1.c)

[用C语言编写的菜单例程（检查是否存在输出重定向）](./ch05_终端/menu2.c)

[用C语言编写的菜单例程（使用/dev/tty）](./ch05_终端/menu3.c)

[用C语言编写的菜单例程（读取每个字符）](./ch05_终端/menu4.c)

[用C语言编写的菜单例程（完整的终端控制）](./ch05_终端/menu5.c)

[使用termios结构的密码程序](./ch05_终端/password.c)

### 第6章 curses

[彩色](./ch06_curses/color.c)

[键盘模式和输入](./ch06_curses/ipmode.c)

[使用keypad模式](./ch06_curses/keypad.c)

[移动、插入和属性](./ch06_curses/moveadd.c)

[管理多窗口](./ch06_curses/multiw1.c)

[使用pad](./ch06_curses/pad.c)

[一个Hello World curses程序](./ch06_curses/screen1.c)

[子窗口](./ch06_curses/subscr1.c)

### 第8章 MySQL

[连接数据库](./ch08_MySQL/connect1.c)

[连接数据库并处理错误](./ch08_MySQL/connect2.c)

[使用mysql_query插入记录](./ch08_MySQL/insert1.c)

[在C程序中使用自动分配的ID](./ch08_MySQL/insert2.c)

[提取数据](./ch08_MySQL/select1.c)

[提取数据并打印](./ch08_MySQL/select2.c)

[提取数据并打印详细信息](./ch08_MySQL/select3.c)

### 第11章 进程和信号

### 第12章 POSIX线程

### 第13章 进程间通信_管道

### 第15章 套接字

