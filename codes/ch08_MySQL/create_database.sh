# 自动生成测试用的用户rick, 数据库foo, 和数据库表children

#! /bin/bash

alias mysql="mysql --socket=/data/mysql.sock"

# 创建用户rick，密码secret
mysql -u root -p12344321 -e "GRANT ALL ON *.* TO rick@'%' IDENTIFIED BY 'secret'"

# 创建数据库foo
mysql -u rick -psecret -e "DROP DATABASE IF EXISTS foo; CREATE DATABASE foo"

# 创建数据库表children
mysql -u rick -psecret foo < create_children.sql

