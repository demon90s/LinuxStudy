#! /bin/bash

# cp 拷贝文件或者目录

# cp 没有给出拷贝过程
test1()
{
    cp ./cp_examples.sh /tmp/cp_examples.sh
}

# cp -vf v表示给出拷贝过程, -f表示强制
test2()
{
    cp -vf ./cp_examples.sh /tmp/cp_examples.sh
}

# cp -i i表示交互模式，会提示是否覆盖文件
test3()
{
    cp -i ./cp_examples.sh /tmp/cp_examples.sh
}

main()
{
    #test1
    #test2
    test3
}

main
