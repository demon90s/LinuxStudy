# git github HowTo

## Git

**创建SSH KEY**

```bash
$ ssh-keygen -t rsa -C "youremail@example.com"
```
在GitHub账号里创建一个SSH key，将`~/.ssh/id_rsa.pub`中的内容加入其中。

**创建版本库**

STEP1: 在Github中创建一个空的远程仓库

STEP2: 克隆一份到本地：

```bash
$ git clone git@github.com:githubname/repos.git
```

**创建分支**

`git branch <branch name>`

查看当前分支：

`git branch`

切换到分支：

`git checkout <branch name>`

删除分支：

`git branch -d <branch name>`

删除远程gihub分支:

`git push origin --delete <branch name>`

**设置提交时用户名和邮箱**

```bash
$ git config --global user.name "demon90s"
$ git config --global user.email demon90s@163.com

$ git config user.name "demon90s"
$ git config user.email demon90s@163.com
```

**提交版本**

```
$ git add *
$ git commit -m "commit log"
$ git push origin master
```

**拉取版本**

```bash
$ git pull origin master
```

**请求帮助**

```bash
$ git help
$ git help add
```

**正确显示中文**

```bash
$ git config core.quotepath false
```

## Github

浏览网站时的快捷键：

```
项目目录中
t 查找文件

浏览代码文件时

l 选择跳转到某一行
e 开启编辑
```

查看远程仓库地址：

```
git remote -v
```