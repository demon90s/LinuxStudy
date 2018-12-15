# Additional GDB notes

---

## 令程序支持gdb调试

需要开启编译选项-g

如果想让程序能生成core文件，需要修改.bashrc，添加`ulimit -c unlimited`。

## 启动调试

**启动并调试一个程序**

```
$ gdb prog
```

**附加进程调试**

```
$ gdb -p PID
```

**调试一个core文件**

```
$ gdb prog core_file
```

## 常用调试命令

```
$ set args [arg_list] # 设置程序的启动参数
$ bt                  # 查看调用堆栈
$ f n                 # 跳到第n个stack frame
$ p variable          # 查看变量内容
$ n                   # step over
$ s                   # step in
$ b file:line         # 在文件的某一行设置断点
$ delete break        # 删除所有的断点
$ q                   # 退出调试
$ c                   # 继续执行程序
$ run                 # 开始执行程序
```

可以这样输出数组中有限数量的元素：

```gdb
(gdb) p array[0]@3
```

如上，输出了数组 array 从第0个元素开始后三个元素。

## 使用脚本调试

gdb加入参数-x script，即可使用脚本调试。

脚本模板：

```gdb
b somewhere [if ... [&&] ... [||] ...]
c
p some_variables
q
```

可以在break后接commands命令，在每次触发断点后直接打印一些值：

```gdb
b somewhere
commands
printf "%d\n", some_number
c
end
c
```

## 调试死循环

直接gdb附加进程后，使用bt命令查看调用堆栈即可。