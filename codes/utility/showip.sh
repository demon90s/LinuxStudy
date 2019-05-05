#! /bin/bash

# 查看本机ip
# usage: ./showip

f_main()
{
    #local internal_ip=$(ifconfig | grep 'inet ' | awk '{print $2}')
    #local public_ip=$(curl myip.ipip.net)

    local internal_ip=$(ifconfig | grep 'inet ' | awk '{print $2}')
    echo "internal ip:"
    for ip in $internal_ip ; do
        echo -e "\t$ip"
    done

    wget myip.ipip.net -O /tmp/myip.$$ -o /tmp/myip.$$.log
    local public_ip_desc=$(cat /tmp/myip.$$)
    rm -f /tmp/myip.$$*
    
    local public_ip=$(echo ${public_ip_desc} | awk '{print $2}' | awk -F '：' '{print $2}')
    local public_area=$(echo ${public_ip_desc} | awk -F '：' '{print $3}')
    echo -e "\npublic ip:"
    echo -e "\t $public_ip From $public_area"
}

f_main $@