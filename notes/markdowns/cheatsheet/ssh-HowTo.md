# ssh-HowTo

使用ssh登陆Linux系统有两种方式：

- 使用密码

- 使用公钥认证，双方各持公钥，客户机还会持有私钥

相对于使用密码，公钥认证的方式更加安全，也方便。

## 基础设置

修改文件：/etc/ssh/sshd_config

设置屏蔽密码：PasswordAuthentication no

设置监听端口: Port 18888

重启sshd服务：

```bash
systemctl restart sshd
```

## 生成密钥

```shell
ssh-keygen -t rsa

# 添加一个注释，设置一个输出文件名字
ssh-keygen -t rsa -C "your comment" -f outputfile
```

连续敲击三次回车生成密钥至目录：`~/.ssh`，id_rsa.pub即是要给服务端的公钥，id_rsa是客户机保留的私钥。

如果是windows系统，则可以使用SecureCRT工具生成：工具->创建公钥，一些关键步骤是：

- 密钥类型选择RSA

- 密钥格式选择OpenSSH

- 可以自定义密钥名

其余保持默认即可。

问题：秘钥登录设置后还是提示需要输入密码（密码登录未取消）

解决：可能是权限的问题，检查：服务器的 .ssh 目录权限是700, authorized_keys 的权限是600

## 加入公钥认证

将公钥的内容加入到文件（服务器）： `~/.ssh/authorized_keys`

## ssh 命令

使用 ssh 登入远程主机，举例：

```bash
ssh -l root -i ~/.ssh/id_rsa 192.168.11.214 -p 18888
```

还可以在后面追加命令。比如：

```bash
ssh -l root -i ~/.ssh/id_rsa 192.168.11.214 -p 18888 "ps aux"
```

如果追加命令，那么默认不登入。还可以查询远程命令的执行结果：`echo $?`

如果登录不了，并提示 sign_and_send_pubkey: signing failed: agent refused operation

那么可能是开启了 ssh-agent 导致的，这时候需要把秘钥添加一下:

```bash
ssh-add private_key
ssh-add -l # 查看
```

## ssh config

编辑 ~/.ssh/config 文件, 可以方便地执行 ssh 命令, 代替各种参数, 如:

```bash
Host txyun
    HostName 118.24.3.169
    User root
    IdentityFile ~/.ssh/Identity_dev
    Port 18888
    ServerAliveInterval 30
```

然后执行 ssh txyun 就可以快速地远程登录了. 

ssh txyun "ps aux" 执行一个远程命令.

## 反向代理/访问内网

使用 ssh 进行反向代理, 使得任意一台计算机通过公网代理服务器访问内网机器.

内网机器开启反向代理:

```bash
# ssh -fCNR 远程端口:localhost:本地ssh监听端口 远程用户@远程ip -p 远程ssh端口
ssh -fCNR 7001:localhost:18888 root@118.24.3.169 -p 18888 -i ~/.ssh/Identity_dev
```

公网代理开启正向代理:

```bash
# ssh -fCNL *:客户端登录端口:localhost:本地端口 localhost -p 本地ssh端口
ssh -fCNL *:7002:localhost:7001 localhost -p 18888 -i ~/.ssh/Identity_dev
```

客户机登录:

```bash
# ssh -p 公网登录端口 内网机器用户名@公网ip地址
ssh -p 7002 diwen@118.24.3.169
```

客户机 config 配置:

```bash
Host *
    ServerAliveInterval 30

Host office
    HostName 118.24.3.169
    User diwen
    IdentityFile ~/.ssh/Identity_dev
    Port 7002
    ServerAliveInterval 30
```

保持反向代理的连接：

我的方法是令公网计算机也设置一个客户机配置，每隔一段时间发送一个 ssh 心跳包。脚本如：

```bash
#! /bin/bash

main()
{
	while true ; do
		ssh office echo "hi office"
		if [ $? ] ; then
			echo $(date)" save connect succ"
		fi
		sleep 30
	done
}
```

将这个脚本设置成后台运行：

```bash
nohup ./save_office_connect.sh >log_save_office_connect.txt 2>&1 &
```
