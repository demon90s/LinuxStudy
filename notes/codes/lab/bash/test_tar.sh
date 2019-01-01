#! /bin/bash

# Usage: tar [OPTION...] [FILE]...

# tar 将许多文件保存为一个归档文件，还可以从归档文件中将其恢复

files="foo.txt bar.txt goo.txt"
archive=arc.tar

# 从 files 创建归档文件 archive
# -c, 创建新归档文件
# -f, 使用归档文件
example1()
{
    tar -cf $archive $files
}

# 详细列出归档文件 archive 中的文件
# -t 列出归档文件的内容
# -v 详细列出已经处理的文件
example2()
{
    tar -tvf $archive
}

# 从归档文件中提取文件
# -x 从归档文件中提取文件
example3()
{
    tar -xf $archive
}

# 压缩存档
# -Z 压缩过滤
# 如果找不到 compress 命令，则 sudo apt install ncompress
example4()
{
    tar -cvZf ${archive}.gz $files
    #tar -xvZf ${archive}.gz $files
}

main()
{
    touch $files

    #example1
    #example2
    #example3
    example4
}

main