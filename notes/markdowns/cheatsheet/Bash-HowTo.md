# Bash HowTo

---

## 输出带颜色的文本

format: \033[n1;n2;n3mYourText

explain:

- \033[ - start escape

- n1, n2, n3 - color or background or attribute

- m - end escape

- YourText - your text to display

[参考代码](../../codes/lab/bash/colors.sh)

## 让进程在后台运行

[参考资料](https://www.ibm.com/developerworks/cn/linux/l-cn-nohup/)

当用户注销（logout）或者网络断开时，终端会收到HUP信号从而关闭其所有子进程。因此，我们可以通过让进程忽略HUP信号阻止这个关闭行为。

nohup的用途就是让提交的命令忽略HUP信号。其用法如：

```bash
$ nohup ping www.ibm.com &
```

&表示让进程在后台运行，nohup让进程忽略HUP信号。nohup默认会将标准输出和标准错误重定向到nohup.out文件中，可以使用">filename 2>&1"来更改这个默认设定。如：

```bash
$ nohup ping www.ibm.com >test_ping.txt 2>&1 &
```

## 修改命令提示符（ Bash Prompt ）

[参考资料](http://www.tldp.org/HOWTO/Bash-Prompt-HOWTO/x157.html)

命令提示符由环境变量 PS1 给出。它默认在 .bashrc 文件中修改，如果需要自定义，那么也应该在这个文件修改。

如果想测试，就直接在终端下输入： PS1=blablabla... 测试。

命令提示符可以有许多的转义序列，表示不同的内容，比如时间、颜色。

修改命令提示符的意义可能是为了分辨当前操作的终端，获取一些操作环境信息。比如，对于 root 用户，最后的提示符通常是 # ，而对于普通用户，通常是 $ 。

常用的转义序列有：

|符号|说明|
|:-:|:-:|
|\u|当前用户的名字|
|\h|主机名|
|\W|当前工作目录|
|\w|当前工作目录的全名|
|\$|如果是root，则为#，否则是$|
|\t|当前的时间，24小时制， HH:MM:SS 格式|
|\e|转义序列033 ，它用于设定后续文本颜色|
|`\[`|开始一个非打印字符序列，通常跟随是颜色设定|
|`\]`|结束一个非打印字符序列|

案例：

|设定|含义|e.g.|
|:-:|:-:|:-:|
|PS1="\u@\h \W> "|用户@主机 工作目录> |diwen@ubuntu ~> |
|PS1="[\u@\h \t\w]\$ "|[用户@主机 时间 工作目录全名]$ |[diwen@ubuntu 12:44:02~/workspace/LinuxStudy]$ |
|PS1='[\[\e[36;1m\]\u@\[\e[32;1m\]fbterm\[\e[31;1m\] \t\[\e[36;1m\]\w\[\e[0m\]]\$ '|[用户(蓝色)@主机(绿色) 时间(红色) 工作目录全名(蓝色)]$ |[diwen@ubuntu 12:44:02~/workspace/LinuxStudy]$|