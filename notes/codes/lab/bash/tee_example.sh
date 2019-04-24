#! /bin/bash

# tee 命令读入标准输入，并将内容写到标准输出和文件（同时）

# tee [OPTION]... [FILE]...

# 将 ls 的输出打印到标准输出以及 out.txt 文件
example1()
{
    ls -l | tee out.txt
}

# 将 ls 的输出连同错误输出输出给 out.txt 文件
example2()
{
    ls noexist 2>&1 | tee out.txt
}

main()
{
    #example1
    example2
}

main