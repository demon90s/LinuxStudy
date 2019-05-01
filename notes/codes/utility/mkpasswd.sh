#! /bin/bash

# 创建随机密码
# usage: ./mkpasswd.sh password_len
# example: ./mkpasswd.sh 6
# example output maybe: TJ94Wt

f_main()
{
    local len=$1
    if [ -z "$len" ] || [ "$len" -lt 1 ] || [ "$len" -gt 20 ] ; then
        len=6
    fi

    local tmp=$(openssl rand -base64 20)
    echo ${tmp:0:$len}
}

f_main $@