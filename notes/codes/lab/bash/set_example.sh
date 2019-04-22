#! /bin/bash

# set为shell设置了参数变量

test1()
{
    set hello world

    echo $0     # 第一个参数没有改变，还是程序名字
    echo $1
    echo $2
}

# set -o nounset
# -o 表示进行一些设置
# nounset 表示如果使用了未定义的变量，输出错误并退出, 返回值非0
test2()
{
    set -o nounset

    #NOSET_VAR=hi
    echo $NOSET_VAR

    echo "Normal return"
}

main()
{
    #test1
    test2
}

main