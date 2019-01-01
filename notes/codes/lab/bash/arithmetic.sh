#! /bin/bash

# 算术运算

# 方法一：使用 $(( expr ))
example1()
{
    expr="3 * 4"
    echo "$expr = $(($expr))"
}

# 方法二：使用 $[ expr ] ，与方法一等价
example2()
{
    expr="3 * 4"
    echo "$expr = $[$expr]"
}

# 方法三，使用 bc 命令，它支持浮点运算，而上面的只支持简单的整数运算
example3()
{
    expr="3 / 4"
    res=$(echo $expr | bc -l)
    echo "$expr = $res"
}

main()
{
    #example1
    #example2
    example3
}

main