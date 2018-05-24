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
```

