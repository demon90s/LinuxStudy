# MySQL操作

操作环境：CentOS 7

如果是虚拟机，除了做端口转发外，可能还需要添加一个远程连接的权限，并执行 iptables -F ，方可使用远程连接。

---

## 基本配置

```bash
# 安装mysql
$ yum install mariadb-server mariadb

# 启动mysql服务
$ systemctl start mariadb.service

# 启动mysql控制台（以root用户登陆）
$ mysql -u root -p

# 查看socket文件路径
$ mysqladmin -u root version | grep "^UNIX socket"

# 设置用户密码
mysql> SET password=PASSWORD('your_password');
mysql> FLUSH PRIVILEGES;

# 去除用户密码
mysql> SET password=PASSWORD('');
mysql> FLUSH PRIVILEGES;

# 创建用户ldw并赋予广泛的权限，其密码是123456
mysql> GRANT ALL ON *.* TO ldw@'%' IDENTIFIED BY '123456';
mysql> FLUSH PRIVILEGES;
```

## 创建数据库和表

### 创建数据库

```bash
# 创建一个数据库 foo
mysql> CREATE DATABASE foo;

# 创建一个数据库 foo ，默认字符集采用 utf8 ，排序规则采用 utf8_general_ci
mysql> CREATE DATABASE foo CHARACTER SET utf8 COLLATE utf8_general_ci;

# 删除数据库 foo
mysql> DROP DATABASE foo;

# 查看数据库列表
mysql> SHOW DATABASES;

# 选择使用默认数据库 foo
mysql> USE foo
```

### 创建表

```bash
# 创建表 bird
# 列  名称               类型            设定
# 1   bird_id           INT             AUTO_INCREMENT PRIMARY KEY
# 2   scientific_name   VARCHAR(255)    UNIQUE
# 3   common_name       VARCHAR(50)
# 4   family_id         INT
# 5   description       TEXT

# AUTO_INCREMENT 代表此列自增，如果没有设置起始数，就从1开始
# PRIMARY KEY 表示此列作为主键，使数据能以其索引
# UNIQUE 表示另一种键的类型
CREATE TABLE birds (
  bird_id INT AUTO_INCREMENT PRIMARY KEY,
  scientific_name VARCHAR(255) UNIQUE,
  common_name VARCHAR(50),
  family_id INT,
  description TEXT);

# 查看表 birds 的表结构
mysql> DESCRIBE birds;

# 删除表 birds
mysql> DROP TABLE birds;

# 创建一张表（工作中总结）
CREATE TABLE `table_name` (
  `table_id` bigint(20) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`table_id`),
  KEY `user_id` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
```

### 插入数据

```bash
# 插入一些数据到 birds 表的 scientific_name 和 common_type 列，一个五行数据
INSERT INTO birds (scientific_name, common_name) 
VALUES ('Charadrius vociferus', 'Killdeer'),
('Gavia immer', 'Great Norhern Loon'),
('Aix sponsa', 'Wood Duck'),
('Chordeiles minor', 'Common Nightawk'),
('Sitta carolinensis', 'White-breasted Nuthatch'),
('Apteryx mantelli', 'North Island Brown Kiwi');

# 查看所有数据
mysql> SELECT * FROM birds;
```

### 深入理解表

```bash
# 查看表 birds 的创建方式
# 这个描述比自己用语句创建时候更加详细，因为它还告诉了服务器采取的默认的设置
mysql> SHOW CREATE TABLE bird \G

*************************** 1. row ***************************
       Table: birds
Create Table: CREATE TABLE `birds` (
  `bird_id` int(11) NOT NULL AUTO_INCREMENT,
  `scientific_name` varchar(255) COLLATE latin1_bin DEFAULT NULL,
  `common_name` varchar(50) COLLATE latin1_bin DEFAULT NULL,
  `family_id` int(11) DEFAULT NULL,
  `description` text COLLATE latin1_bin,
  PRIMARY KEY (`bird_id`),
  UNIQUE KEY `scientific_name` (`scientific_name`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1 COLLATE=latin1_bin
```

## 其他操作

```bash
# 通过非交互模式运行mysql
$ mysql -u ldw --password=123456 foo < sqlcmd.sql
$ mysql -uroot -p foo -e 'SELECT * FROM boo'

# 转储数据库
$ mysqldump -u ldw -p db_name > db_name_bak.sql

# 转储数据库中的某个表
$ mysqldump -u ldw -p db_name table > table_bak.sql
```

## MySql 函数

FROM_UNIXTIME - 将时间戳转换成字符串表示的时间

COUNT(\*) - 得到记录的总数目