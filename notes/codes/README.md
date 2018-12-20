# Linux程序设计

学习环境：CentOS 7

对于第五章和第六章使用了头 curses.h 和 term.h 中的功能，需要安装 curses 开发包：yum install ncurses-devel.x86_64，并在构建程序时加入链接选项 -lncurses

对于第七章的 dbm 库的使用，需要安装 gdbm 开发包：yum install gdbm-devel.x86_64，并在构建程序时加入链接选项 -lgdbm -lgdbm_compat

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

### 第7章 数据管理

[一个简单的dbm数据库](./ch07_数据管理/dbm1.c)

[检索和删除](./ch07_数据管理/dbm2.c)

[创建锁文件](./ch07_数据管理/lock1.c)

[协调性锁文件](./ch07_数据管理/lock2.c)

[使用 fcntl 锁定文件](./ch07_数据管理/lock3.c)

[测试文件上的锁](./ch07_数据管理/lock4.c)

[文件锁的竞争](./ch07_数据管理/lock5.c)

[简单的内存分配](./ch07_数据管理/memory1.c)

[请求全部的物理内存](./ch07_数据管理/memory2.c)

[可用内存](./ch07_数据管理/memory3.c)

[滥用内存](./ch07_数据管理/memory4.c)

[访问空指针](./ch07_数据管理/memory5.c)

[释放内存](./ch07_数据管理/memory6.c)

### 第8章 MySQL

[连接数据库](./ch08_MySQL/connect1.c)

[连接数据库并处理错误](./ch08_MySQL/connect2.c)

[使用mysql_query插入记录](./ch08_MySQL/insert1.c)

[在C程序中使用自动分配的ID](./ch08_MySQL/insert2.c)

[提取数据](./ch08_MySQL/select1.c)

[提取数据并打印](./ch08_MySQL/select2.c)

[提取数据并打印详细信息](./ch08_MySQL/select3.c)

### 第9章 开发工具

[一个简单的makefile文件](./ch09_开发工具/Makefile1)

[带宏定义的makefile文件](./ch09_开发工具/Makefile2)

[多个目标](./ch09_开发工具/Makefile3)

[管理函数库](./ch09_开发工具/Makefile5)

### 第10章 调试

[assert](./ch10_调试/assert.c)

[valgrind](./ch10_调试/checker.c)

[调试信息](./ch10_调试/cinfo.c)

[ElectricFence](./ch10_调试/efence.c)

### 第11章 进程和信号

[发送信号](./ch11_进程和信号/alarm.c)

[fork函数](./ch11_进程和信号/fork1.c)

### 第12章 POSIX线程

### 第13章 进程间通信_管道

[mkfifo](./ch13_进程间通信_管道/fifo1.c)

[打开 FIFO 文件](./ch13_进程间通信_管道/fifo2.c)

[使用 FIFO 实现进程间通信](./ch13_进程间通信_管道/fifo3.c)

[使用 FIFO 实现进程间通信](./ch13_进程间通信_管道/fifo4.c)

[pipe 函数](./ch13_进程间通信_管道/pipe1.c)

[跨越 fork 调用的管道](./ch13_进程间通信_管道/pipe2.c)

[管道和 exec 函数，生产者程序](./ch13_进程间通信_管道/pipe3.c)

[管道和 exec 函数，消费者程序](./ch13_进程间通信_管道/pipe4.c)

[管道和dup函数](./ch13_进程间通信_管道/pipe5.c)

[读取外部程序的输出](./ch13_进程间通信_管道/popen1.c)

[将输出送往popen](./ch13_进程间通信_管道/popen2.c)

[通过管道读取大量数据](./ch13_进程间通信_管道/popen3.c)

[popen 启动 shell](./ch13_进程间通信_管道/popen4.c)

### 第14章 信号量_共享内存_消息队列

[消息队列（接收消息）](./ch14_信号量_共享内存_消息队列/msg1.c)

[消息队列（发送消息）](./ch14_信号量_共享内存_消息队列/msg2.c)

[信号量](./ch14_信号量_共享内存_消息队列/sem1.c)

[共享内存（消费者程序）](./ch14_信号量_共享内存_消息队列/shm1.c)

[共享内存（生产者程序）](./ch14_信号量_共享内存_消息队列/shm2.c)

### 第15章 套接字

### 第16章 用GTK+进行GNOME编程

[构建容器布局](./ch16_用GTK+进行GNOME编程/container.c)

[一个空白的Gtkindow](./ch16_用GTK+进行GNOME编程/gtk1.c)

[回调函数](./ch16_用GTK+进行GNOME编程/gtk2.c)

