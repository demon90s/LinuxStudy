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

# 使用 bc 进行进制转换
example4()
{
    number=20
    echo -e "dec 20 -> hex \c"
    echo "obase=16;20" | bc

    echo -e "dec 20 -> bin \c"
    echo "obase=2;20" | bc
}

main()
{
    #example1
    #example2
    #example3
    example4
}

main