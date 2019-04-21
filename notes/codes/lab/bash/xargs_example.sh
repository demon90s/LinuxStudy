#! /bin/bash

# xargs 将参数转换成小块传递给其他命令

test1()
{
    # 将每一个 sh 文件的 md5 值输出出来
    echo *.sh | xargs md5sum
}

# xargs 会比 find 的 -exec 要高效的多
test2()
{
    time find . -maxdepth 1 -name "*.sh" -exec md5sum {} \;

    time find . -maxdepth 1 -name "*.sh" | xargs md5sum
}

main()
{
    #test1
    test2
}

main
