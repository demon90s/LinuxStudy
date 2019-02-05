/*
    #include <arpa/inet.h>
    inet_pton(int af, const char* ip, void *dst);
    将 ip 地址转换成网络地址结构。
    af 取值可以是 AF_INET, AF_INET6
    如果是 AF_INET , 此时 dst 所指向的类型应该是 struct sockaddr_in 之 成员 sin_addr 类型。即 struct in_addr 类型。 

    函数返回1代表成功，0代表 ip 中有字符格式不符，-1表示 af 不支持。
*/

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void test_inet_pton()
{
    const char* ip = "127.0.0.1";
    struct in_addr addr;
    int ret;

    ret = inet_pton(AF_INET, ip, &addr);
    if (ret == 1) {
        printf("convert succ, ip(%s) -> addr(%ul)\n", ip, addr.s_addr);
    }
    else if (ret == 0) {
        printf("ip(%s) format incorrect\n", ip);
    }
    else {
        perror("inet_pton");
    }
}

int main()
{
    test_inet_pton();

    return 0;
}