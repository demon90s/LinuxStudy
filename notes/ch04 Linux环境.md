# 第四章 Linux环境

---

## 程序参数

一个C语言程序从 main 函数开始，它的声明如：

```c
int main(int argc, char *argv[]);
```

其中， argc 是程序的参数的个数， argv 是程序的参数列表。

这些参数通常由 shell 提供。例如，在 shell 中执行程序 myprog ：

```shell
$ myprog left right 'and center'
```

那么 argc 为4，而 argv 是 { "myprog", "left", "right", "and center", NULL };

### getopt

程序参数有一定的准则，比如：以 - 开头的，叫选项，后面可以跟着一个关联值。为了方便应用这样的准则， Linux 提供了 getopt 函数，它可以抓取选项和选项的值。

### getopt_long

getopt 不能够处理 -- 这样的长选项，这样的选项可以交给 getopt_long 处理。

## 环境变量

环境变量是一些能用来控制 shell 脚本和其他程序行为的变量。比如，每一个用户都有一个环境变量 HOME ，代表用户家目录，它是用户会话开始时候的默认目录。

通过 getenv 和 putenv 可以获取/设置当前程序的环境变量。

### 环境变量的用途

程序经常使用环境变量来改变它们的工作方式。可以这样把环境变量 FRED 传递给一个程序 program ：

```shell
$ FRED=hello ./program
```

也可以这样：

```shell
$ FRED=hello; export FRED
$ ./program
```

!!!warning
    环境变量就像全局变量一样，会使得程序的调试变得困难。

### envrion 变量

每一个环境由一组格式为 "名字=值" 的字符串组成。这些字符串可以通过 environ 变量访问，它是一个全局的字符串数组，并以空指针结尾。

## 时间和日期

所有的 UNIX 系统都使用同一个时间和日期的起点：格林尼治时间（GMT）1970年1月1日0点。

时间通过一个预定义的类型 time_t 来处理。在 Linux 中，它是一个长整型。

通过 time 函数可以获取当前的底层时间值。

时间值可以转换成一个分解结构，包含了更加详细的时间信息。

通过 gmtime 和 localtime 可以获取这个结构。

通过 mktime 可以将分解时间转换回底层时间值。

更快速地获取到友好的时间字符串表示，可以使用 asctime ctime strftime 。

## 临时文件

很多情况下，程序会利用一些临时文件作为临时存储手段。必须要保证临时文件的文件名是唯一的，不然多个程序直接用到同一个文件就会相互干扰。

通过 tmpnam 可获取一个唯一的文件名。

通过 tmpfile 可以打开一个临时文件，这个文件会在所有引用关闭时被自动删除。

但 GNU C编译器会对 tmpnam 给出警告信息。

UNIX 还提供了另一种生成临时文件名的方式，就是使用 mktemp 和 mkstemp 函数。

## 用户信息

除了 init 程序，所有的 Linux 程序都是由其他程序或用户启动的。

用户通常是在一个响应他们命令的 shell 中启动程序。程序也可以发现它的使用者的相关信息。

一个用户登进 Linux 系统，需要一个用户名和密码，用户名还关联着一个唯一的标识符 UID 。

使用 getuid 可以获取程序关联的 UID ，使用 getlogin 获取的是用户名。它们通常是启动程序的用户。

用户的账号数据库是文件 `/etc/passwd` 。这是一个普通用户不能读取的文件，但可以通过编程接口访问，也就是通过 getpwuid 或 getpwnam 。

## 主机信息

程序还可以获得运行它的计算机的有关细节。 uname 命令就可以直接获取。比如 `uname -a` 。

系统提供了同名的C接口，获取同样的信息。

gethostname 获取了主机的网络名。

## 日志

许多应用程序需要记录它们的活动。系统程序经常需要向控制台或日志文件写消息。

日志文件有：

- `/var/log/message` - 记录系统信息

- `/var/log/mail` - 记录包含来自邮件系统的其他日志信息

- `/var/log/debug` - 可能包含调试信息

通过查看 /etc/syslog.conf 或 /etc/syslog-ng/sys-log-ng.conf 文件来检查系统配置。

!!!note
    在 CentOS 7上面没有发现这个系统配置。

通过 syslog 函数可以写这样的日志。

通过 closelog openlog setlogmask 可以改变日志信息的表述方式。

## 资源限制

Linux 系统上运行的程序会受到资源限制的影响。比如内存、文件数量、文件名长度等。

头文件 limits.h 中定义了许多操作系统方面限制的常量。比如 NAME_MAX CHAR_BIT INT_MAX 。

头文件 sys/resource.h 提供了资源操作方面的定义，其中包括对程序长度、执行优先级和文件资源等方面限制进行查询和设置的函数：

- getpriority/setpriority , 用来获取/设置进程优先级

- getrlimit/setrlimit , 用来获取/设置各种资源限制

- getrusage , 用来查询 CPU 时间