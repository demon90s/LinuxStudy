# MySQL操作

操作环境：CentOS 7

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

# 去除用户密码
mysql> SET password=PASSWORD('');

# 创建用户ldw并赋予广泛的权限
mysql> GRANT ALL ON foo.* TO ldw@'%' IDENTIFIED BY '123456';
```

## MySQL操作

```bash
# 通过非交互模式运行mysql
$ mysql -u ldw --password=123456 foo < sqlcmd.sql
$ mysql -uroot -p123456 foo -e 'SELECT * FROM boo'

# 转储数据库
$ mysqldump -u ldw -p123456 table_name > table_name_bak.dump

# 创建一个数据库
mysql> CREATE DATABASE test;

# 查看所有数据库
mysql > SHOW DATABASES;

# 删除一张表
mysql > DROP TABLE table_name;

# 创建一张表（脚本）
CREATE TABLE `table_name` (
  `table_id` bigint(20) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`table_id`),
  KEY `user_id` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
```