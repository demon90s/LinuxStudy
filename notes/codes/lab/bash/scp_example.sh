#! /bin/bash

# scp 远程拷贝
# scp [options] src target
# -r 参数可以拷贝目录

# 从服务器上拷贝文件到本地
f_example1()
{
    # -i 指定秘钥文件
    # -P 指定远程端口
    scp -i ~/.ssh/Identity_dev -P 18888 root@118.24.3.169:/root/tmp/test.txt /tmp/

    cat /tmp/test.txt
}

# 从本地拷贝文件到服务器
f_example2()
{
    scp -i ~/.ssh/Identity_dev -P 18888 ./scp_example.sh root@118.24.3.169:/root/tmp/
}

# 设置超时时间
# -oConnectTimeout=seconds
f_example3()
{
	scp -oConnectTimeout=3 root@192.168.11.214:~/tmp.txt .
}

f_main()
{
    #f_example1
    #f_example2
	f_example3
}

f_main $@
