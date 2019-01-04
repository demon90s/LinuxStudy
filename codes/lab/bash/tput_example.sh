#! /bin/bash

# tput 初始化一个终端，或者访问 terminfo 数据库

# 设置终端的光标位置到 (y10, x4)
example1()
{
    tput cup 10 4
    echo "this is line 10"
}

# 清屏，并重置光标位置，到 (y1, x1) ，注意，(y0, x0) 是左上角
example2()
{
    tput reset
    echo "Reset position"
}

main()
{
    #example1
    example2
}

main