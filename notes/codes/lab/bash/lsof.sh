# lsof (list open files) 可以查看系统文件信息. 
# Linux 中, 一切皆文件, 这个命令可以看许多文件信息, 比如普通文件, 目录, 网络文件等等.

# 列出指定进程打开的文件 (-c)
test1()
{
    # prog 是进程名字, 无须说明执行路径
    lsof -c prog
}

# 列出某个进程号打开的文件 (-p)
# 如果是 FD 列的值是 255r, 那么表示使用sh执行的该脚本文件, 试试 sh lsof.sh
test2()
{
    lsof -p $$
}

# 列出某个进程号打开的关于 IPV4 的连接信息
test3()
{
    lsof -i 4 -a -p 6789
}

# 列出谁在使用某个端口
test4()
{
    lsof -i :3306
}

main()
{
    test2 
}

main
