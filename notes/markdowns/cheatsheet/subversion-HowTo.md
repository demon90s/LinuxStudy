# subversion-HowTo

---

## 安装 SVN

CentOS7 可能已经默认安装了 SVN 服务器，输入下列命令验证：

```bash
svnserve --version
```

但可能没有安装 svn 客户端，使用下列命令安装：

```bash
yum install svn
svn --version
```

如果是 Ubuntu 系统，可以这样安装客户端：

```bash
sudo apt-get install subversion
```

## 搭建仓库

```bash
# 创建一个仓库
mkdir -p /data/repo
cd /data/repo
svnadmin create .

# 创建一个项目
cd
mkdir project
svn import project file:///data/repo/project -m "初始化"
rm -fr project

# 启动svn服务
# 加入 --listen-port=3680 这样的选项，可以设置服务端口号为3680，默认是3690
svnserve -d -r /data/repo

# 拉取项目，如果是从另一台机器拉，则把IP地址改成对外的地址
svn co svn://127.0.0.1:3690/project
```

## 添加用户/权限设定

进入到仓库目录的conf目录，修改 svnserve.conf 文件中的一些字段：

```
anon-access = none #禁止其它用户的访问
auth-access = write
password-db = passwd
authz-db = authz
```

如果要添加一个用户，修改 passwd 文件。

如果要给用户权限，修改 authz 文件。

修改 passwd 和 authz 目录后，不需要重启服务也可生效。

## 强制提交日志字数限制

修改 svn 版本库中的 hooks/pre-commit 脚本文件（如果没有，则添加），在脚本结束前，写入：

```bash
# 日志内容不得少于10个字符
LOGMSG=`$SVNLOOK log -t "$TXN" "$REPOS" | grep "[a-zA-Z0-9]" | wc -c`
if [ "$LOGMSG" -lt 10 ];
then
  echo -e "Log message too short. Commit aborted!" 1>&2
  exit 1
fi
```

然后 chmod + x 给予脚本可执行权限。

注意，还需要把上面 # Make sure that ... 的脚本注释掉。

## 加入外部项目

使用 TortoiseSVN 客户端的方法：

1. 右键仓库目录空白处 -> SVN -> 属性，点击新建 -> 外部 -> 新建

2. 输入一个目录名字作为外部项目的目录。

3. URL 输入外部项目的地址，如：^/engine ，^代表本仓库的地址前缀。

4. 确定，然后更新 SVN ，即可。

## 合并代码

使用 TortoiseSVN 客户端的方法：

1. 右键项目目录 -> TotoriseSVN -> Merge

2. 合并一个版本范围

3. 选择合并源，指定版本

4. 合并

## 一些 svn 命令

```bash
# 签出工作副本 workspace ，从 url:port ，可以忽略掉 port ，这时使用默认的端口号 3690
# 本地的目录新建为 working_copy ，可以忽略这个参数，此时就使用 workspace 作目录名
svn checkout svn://url:port/workspace working_copy

# 可以加入下面的设置来指定一个用户
svn co --username name --password passwd svn://url:port/workspace

# 查看当前目录的文件状态
svn status

# 查看 path 下的文件状态
svn status path

# 设置 changelist ，比如设置一个忽略提交的 ignore-on-commit 集合，把不想提交的 file 放进去
svn changelist ignore-on-commit file

# 把文件 file 从它所在的 changelist 集合中删掉
svn changelist --remove file

# 查看日志（最后5个提交日志）
svn log -l 5

# 提交文件 file1, file2, 提交日志为 commit log
svn commit -m "commit log" file1 file2

# 把文件 file 加入版本控制，file 也可以是目录
svn add file

# 恢复文件 file ，放弃本地的更改
svn revert file

# 恢复目录 dir 和其文件，放弃本地的更改
svn revert -R dir

# 查看文件 file 的本地修改
# 如果想使用 vimdiff 替换掉 svn diff ，可以参考：https://stackoverflow.com/questions/7866286/how-to-view-svn-diff-in-vimdiff-style-in-svn
svn diff file

# 查看目录或者文件的最后版本，如果是目录，那么第一行是.的版本号信息
svn -v list dir
```

## revision 与关键字

revision 指的是版本号，每次提交版本号都会+1 。使用 --revision REV 指定版本号为 REV ，使用 --revision REV1:REV2 来指定一个版本范围。

REV 还可以是一些关键字：

- HEAD ，表示版本库中的版本号

- BASE ，表示工作服本中的某一个文件的“原始未变更”版本号（意思是本地最后一次 Update 它时候的版本号）

- COMMITTED ，表示某一个文件在 BASE 之前最后一次变更的版本号。

- PREV ，是 CIMMITTED - 1

REV 还可以是一些时间：

--revision {2019-01-01}

