#include <linux/msg.h>
#include <stdio.h>

/*
    消息队列所用宏定义
    MSGMAX 代表一条消息最大长度(字节)
    MSGMNB 代表一个队列的最大长度(字节)
*/

int main()
{
    printf("MSGMAX: %d\n", MSGMAX); // 8192
    printf("MSGMNB: %d\n", MSGMNB); // 16384

    return 0;
}
