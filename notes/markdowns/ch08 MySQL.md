# 第八章 MySQL

MySQL是一种关系型数据库管理系统（RDBMS，Relation Database Management System）。

MySQL是开源的。

虽然MySQL在许多场合下的使用是遵循GPL的，但是也有许多场合下必须购买它的商业许可证才能使用它。

MySQL读如"my sequel"。

---

## 安装

CentOS 7已经安装好了MySQL，如果没有安装，则使用下面命令安装：

```bash
$ yum install mariadb-server mariadb
```

启动的命令是：

```bash
$ systemctl start mariadb.service
$ mysql
```

其他安装方法见书本。

### 安装后的配置

安装完后，输入：

```bash
$ mysql -u root mysql
```

如果进入到MySQL控制台，就表示服务器正在运行。输入\s可得到更多关于服务器的信息。输入quit或\q退出控制台。

使用命令`mysql -?`可以获得更多有关服务器的信息，此命令的输出中，有一条`Default options are read from the following files in the given order:`，它告诉你在哪里可以找到配置文件，此配置文件用于配置MySQL服务器，通常是`/etc/my.cnf`。

使用mysqladmin命令查看正在运行的服务器状态以及服务器的版本号：

```bash
$ mysqladmin -u root version
```

输出正在运行的服务器中所有的配置选项：

```bash
$ mysqladmin variables -u root
```

其中有几个特别有用的变量：

- datadir，表示MySQL在哪里存储它的数据。

- have_innodb，通常是YES，表明MySQL服务器支持InnoDB存储引擎。

- default_storage_engine，当前MySQL服务器使用的存储引擎。

为了把InnoDB设置成默认存储引擎，需要修改MySQL服务器配置文件，在mysqld一节中添加：

```
default_storage_engine=InnoDB
```

更多信息可访问：[MySQL官网](www.mysql.com)

**用户密码设置**

MySQL的root用户和系统的root用户毫无关系。MySQL只不过默认使用一个称为"root"的用户作为管理用户。

一个最简单的设置密码的命令：

```bash
$ mysqladmin -u root password newpassword
```

或者：

```bash
$ mysql -u root
mysql> SET password=PASSWORD('newpassword');
```

如果想删除密码，则可以：

```bash
mysql> SET password=PASSWORD('');
```

一条SQL命令以分号结尾，严格来说，分号不属于SQL命令的一部分，它只是用来告诉MySQL客户端程序，一条SQL语句已经准备好被执行了。

SQL关键字不区分大小写，但使用大写可以便于阅读。

设置了密码的用户，必须提供密码参数才能登陆MySQL客户端程序：

```bash
$ mysql -u root -p
```

**检查权限表确认密码设置**

```bash
mysql> use mysql
mysql> SELECT user, host, password FROM user;
```

MySQL不仅能为用户保存不同的权限，也能为基于主机名的连接类保存不同的权限。

**添加用户**

以root用户身份连接到MySQL，然后使用grant命令来创建用户并赋予权限。

例子：

为ldw创建一个本地登录：

```bash
mysql> GRANT ALL ON *.* TO ldw@localhost IDENTIFIED BY '123456';
mysql> SELECT user, host, password FROM mysql.user;
```

IDENTIFIED BY是一个用于设定初始密码的语法。

`*.*`给予了用户非常广泛的权限。

### 安装后的故障修复

如果连接mysql失败，可使用ps命令检查服务器进程是否正在运行：`ps aux | grep mysql`

在CentOS 7上面，可以使用这个命令检查：`systemctl status mariadb.service `

其它的方法见书本。

## MySQL管理

包含在MySQL发行版中的一些有用的工具程序使管理工作变得容易。

### 命令

除了mysqlshow命令外，所有的MySQL命令都接受如下3个标准参数：

|命令选项|参数|说明|
|-|-|-|
|-u|用户名|指定一个用户名作为MySQL的用户名，默认情况下，mysql工具会尝试把当前的Linux用户名作为MySQL用户名|
|-p|[密码]|如果给出了-p参数但是未提供密码，系统会提示输入密码。若没给-p参数，MySQL命令假设不需要密码|
|-h|主机名|用于连接位于不同主机上的服务器。对于本地服务器，总是可以省略|

**mysql命令**

这是MySQL一个主要的且功能强大的命令行工具。

默认使用数据库foo来启动控制台（客户端）的命令如：

```bash
$ mysql -u ldw -p foo
```

通过非交互模式运行mysql：

```bash
$ mysql -u ldw --password=123456 foo < sqlcmd.sql
```

当mysql客户端连接到服务器后，除了标准的SQL92命令集以外，还有一些特定的命令被mysql支持。如：

|命令|说明|
|-|-|
|help|显示命令列表|
|edit|编辑命令|
|exit或quit|退出MySQL客户端|
|go|执行命令|
|source `<filename>`|从指定文件执行SQL|
|status|显示服务器状态信息|
|system `<command>`|执行一个系统命令|
|tee `<filename>`|把所有输出的副本添加到指定文件中|
|use `<database>`|使用给定的数据库|

MySQL最常使用的术语是database，它是一个基本独立的表格集。可以为每个数据库指定不同的用户，只要拥有适当的权限，就可以通过use命令在不同的数据库之间进行切换。

特定数据库mysql是由MySQL安装自动创建的，它用于保存如用户和权限这样的数据。

**mysqladmin**

快速进行MySQL数据库管理的主要工具。除了常见参数，还支持如下命令：

|命令|说明|
|-|-|
|create `<database_name>`|创建一个新数据库|
|drop `<database_name>`|删除一个数据库|
|password `<new_password>`|修改密码|
|ping|检查服务器是否正在运行|
|reload|重载控制权限的grant表|
|status|提供服务器的状态|
|shutdown|停止服务器|
|variables|显示控制MySQL操作的变量及其当前值|
|version|提供服务器的版本号以及它持续运行的时间|

如果不带参数调用mysqladmin命令，就可以从命令提示符下看到完整的选项列表。

**mysqldump**

mysqldump命令允许以SQL命令集的形式将部分或整个数据库导出到一个单独的文件中，该文件能被重新导入MySQL或其他的SQL RDBMS。

以下参数扩展了这个工具的功能：

|命令|说明|
|-|-|
|-add-drop-table|添加SQL命令到输出文件，以在创建表的命令之前丢弃（删除）任何表|
|-e|使用扩展的insert语法|
|-t|只转储表中的数据，而不是用来创建表的信息|
|-d|只转储表结构，而不是实际数据|

默认情况下，mysqldump将数据发送到标准输出，可以把它重定向到文件。

mysqldump命令对于迁移数据或快速备份非常有用。

一个转储数据库的例子：

```bash
$ mysqldump -u ldw -p table_name > table_name_bak.dump
```

**mysqlimport**

mysqlimport命令用于批量将数据导入到一个表中。

**mysqlshow**

这个小工具能够让你快速了解MySQL安装及其组成数据库的信息。

- 不提供参数，列出所有可用的数据库。

- 以一个数据库为参数，列出该数据库中的表。

- 以数据库和表名为参数，列出表的列。

- 以数据库、表和列为参数，列出指定列的详细信息。

### 创建用户并赋予权限

MySQL管理员最常见的工作就是维护用户信息——在MySQL中添加和删除用户并管理他们的权限。

通过在MySQL控制台中使用grant和revoke命令来管理用户权限。

**grant命令**

MySQL的grant命令几乎完全遵循SQL92的语法。其常规格式是：

```bash
grant <privilege> on <object> to <user> [identified by user-password] [with grant option];
```

可以授予的特权值见书本。

授予特权的对象被标识为：database_name.table_name

在Linux传统中，\*代表通配符，因此\*.\*代表每个数据库中的每个对象，foo.\*代表数据库foo中的每个表。

如果指定的用户已经存在，他的特权会被编辑以反映所做的修改。如果用户不存在，他就会以指定的特权被创建。

在SQL语法中，特殊字符%代表通配符，它与shell环境中的\*号的作用完全一致。任何时候使用%通配符都必须把它放到引号中，以与其他文本分开。

创建一个可以从任何主机进行连接的用户：

```bash
mysql> GRANT ALL ON foo.* TO ldw@'%' IDENTIFIED BY '123456';
```

**revoke命令**

管理员可以剥夺用户的权限。通过revoke命令：

```
revoke <a_privilege> on <an_object> from <a_user>
```

如：

```bash
mysql> REVOKE INSERT ON foo.* FROM rick@'%';
```

revoke命令不能删除用户，如果要完全删除一个用户，不要只是修改他们的权限，而应用revoke来删除他们的权限。然后，切换到mysql数据库，通过从user表中删除相应的行来完全删除一个用户：

```bash
mysql> use mysql
mysql> DELETE FROM USER WHERE user = "ldw";
mysql> FLUSH PRIVILEGES;
```

FLUSH PRIVILEGES告诉服务器，需要重载权限表。

### 密码

如果想为尚未拥有密码的用户指定密码，或者希望改变自己或别人的密码，你就需要以root用户身份连接到MySQL服务器，然后直接更新用户信息。例如：

```bash
mysql> use mysql
mysql> UPDATE user SET password = password('bar') WHERE user = 'ldw';
mysql> FLUSH PRIVILEGES;
```

### 创建数据库

创建一个数据库的命令可以是：

```bash
mysql> CREATE DATABASE test;
```

### 数据类型

MySQL的数据类型非常标准，书本里只做了简要的浏览，MySQL网站上的MySQL手册对此进行了更为详细的讨论。

见书本。

### 创建表

一个数据库表非常像电子表格，除了每行都必须包含相同数目和类型的列，而且每行必须以某种方式不同于表中的其他行。

创建数据库对象的完整SQL语法被称为DDL（data definition language, 数据库定义语言）。

见书本。

### 图形化工具

我使用工作上用的navicat, 其它工具见书本。

## 使用C语言访问MySQL数据库

可以使用许多不同的编程语言来访问MySQL，比如C, C++, PHP, Python。在此讨论C语言的接口。

### 连接例程

见connect1.c。

用C语言连接MySQL数据库包含两个步骤：

- 初始化一个连接句柄结构；

- 实际进行连接。

使用mysql_init来初始化连接句柄：

```c
#include <mysql.h>
MYSQL *mysql_init(MYSQL *);
```

如果传递给NULL给此接口，它会返回一个指向新分配的连接句柄结构的指针。如果传递一个已有结构，它将被重新初始化。出错时返回NULL。

使用mysql_real_connect来向一个连接提供参数：

```c
MYSQL *mysql_real_connect(MYSQL *connection,
    const char *server_host,
    const char *sql_user_name,
    const char *sql_password,
    const char *db_name,
    usigned int port_number,
    const char *unix_sock_name,
    unsigned int flags);
```

connection必须指向已经被mysql_init初始化过的结构。server_host是主机名（可以是IP地址，或者localhost）。sql_user_name和sql_password和字面含义一样。

port_number和unix_socket_name默认为0和NULL，表示采用MySQL的默认设置。

flag参数默认填0即可，对于介绍性的章节来说，没什么用。

使用完连接之后，通常在程序退出时，调用mysql_close关闭连接：

```c
void mysql_close(MYSQL *connection);
```

如果connection是由mysql_init建立的，MYSQL结构会被释放，指针将会失效并无法再次使用。

mysql_options仅能在mysql_init和mysql_real_connect之间调用，可以设置一些选项。见书本。

### 错误处理

见connect2.c。

MySQL使用一系列由连接句柄结构报告的返回码。两个必备的例程是：

```c
unsigned int mysql_errno(MYSQL *connection);
char *mysql_error(MYSQL *connection);
```

mysql_errno获得错误码，如果未设定错误，它将返回0。因为每次调用库都会更新错误码，所以只能得到最后一个执行命令的错误码，但上面两个例程是例外，它们不会导致错误码更新。

mysql_error获得文本错误信息，这些信息被写入一些内部静态内存空间中，如果想保存错误文本，需要把它复制到别的地方。

### 执行SQL语句

见insert1.c。

执行SQL语句的主要API函数为：

```c
int mysql_query(MYSQL *connection, const char *query);
```

query是字符串形式的有效SQL语句（没有结束的分号）。如果成功，返回0。对于包含二进制数据的查询，可以使用mysql_real_query。

用于检测受影响的行数的函数：

```c
my_ulonglong mysql_affected_rows(MYSQL *connection);
```

返回一个my_ulonglong类型是出于移植性的考虑，可以把它转换成无符号长整型。函数返回受之前的UPDATE, INSERT, DELETE查询影响的行数。

通常返回值0表示没有行受到影响，正数则是实际的结果，一般表示受语句影响的行数。如果是DELETE删除整个表的数据，由程序返回的结果是0。

**发现插入的内容**

见insert2.c。

如果一个列的类型是AUTO_INCREMENT，那么它会由MySQL自动分配ID。如何知道刚刚插入的记录的这个ID呢？

MySQL提供了LAST_INSERT_ID()函数，无论何时MySQL向AUTO_INCREMENT列中插入数据，MySQL都会基于每个用户对最后分配的值进行跟踪。用户可以这样发现该值：

```c
mysql> SELECT LAST_INSERT_ID();
```

返回的数字在本次会话中是唯一的。

**返回数据的语句**

见select\*.c。

数据是使用SELECT语句提取的。

在C应用程序中提取数据一般需要下面4个步骤：

- 执行查询；

- 提取数据；

- 处理数据；

- 必要的清理工作。

使用完mysql_qurey发送SQL语句后，使用mysql_store_result或mysql_use_result来提取数据。接着使用一系列mysql_fetch_row调用来处理数据。最后使用mysql_free_result释放查询占用的内存资源。

**一次提取所有数据的函数**

可以使用mysql_store_result在一次调用中从SELECT中提取所有数据：

```c
MYSQL_RES *mysql_store_result(MYSQL *connection);
```

需要在成功调用mysql_query之后使用此函数。这个函数将立刻保存在客户端中返回的所有数据。它返回一个指向结果集结构的指针，如果失败则返回NULL。

mysql_num_rows返回记录的数据，如果没有返回行，这个值将是0。

```c
my_ulonglong mysql_num_rows(MYSQL_RES *result);
```

接下来，可以使用mysql_fetch_row来处理结果集，也可以使用mysql_data_seek, mysql_row_seek, mysql_row_tell在数据集中来回移动。

mysql_fetch_row: 这个函数从结果集中提取一行数据，并把它放到一个行结构中。当数据用完或发生错误时返回NULL。

```c
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
```

在完成了对结果集的操作后，必须总是调用mysql_free_result函数来让MySQL库清理它分配的对象：

```c
void mysql_free_result(MYSQL_RES *result);
```

**一次提取一行数据**

依靠mysql_use_result可以逐行提取数据：

```c
MYSQL_RES *mysql_use_result(MYSQL *connection);
```

mysql_use_result在遇到错误时返回NULL。如果成功，返回指向结果集对象的指针。但是，它未将提取的数据放到它初始化的结果集中。

在之后使用mysql_fetch_row返回行结果必须通过网络。

**处理返回的数据**

MySQL返回两种类型的数据：

- 列数据，即从表中提取的信息

- 元数据（matadata），如列名和类型

mysql_field_count函数返回结果集中的字段（列）数目：

```c
unsigned int mysql_field_count(MYSQL *connection);
```

使用mysql_fetch_field函数可以将元数据和数据提取到一个新的结构中：

```c
MYSQL_FIELD *mysql_fetch_field(MYSQL_RES *result);
```

此函数需要重复调用，直到返回表示数据结束的NULL值为止。MYSQL_FIELD包含了关于列的信息。见书本。

### 更多的函数

见书本。