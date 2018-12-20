/*
    #include <sys/msg.h>
    int msgsnd(int msgid, const void *msg_ptr, size_t msg_sz, int msgflg);
    ssize_t msgrcv(int msgid, void *msg_ptr, size_t msg_sz, long int msg_type, int msgflg);

    msgsnd 把消息（ msg_ptr 所指内容的副本）添加到消息队列中。
    消息队列的结构地址由 msg_ptr 给出，它的长度必须小于系统规定的上限，且必须以一个长整型成员开始。
    如：
    struct my_message {
        long int message_type;
        data...
    };

    msg_sz 是 data 的长度。

    msgflg 用于控制消息队列满或队列消息达到系统范围的限制时将要发生的事情。如果设置了 IPC_NOWAIT 
    标志，函数将立即返回，不发送消息并且返回值为-1 。若没有此标记，进程将被刮起直到有空间为止。

    函数成功返回0，失败返回-1 。

    msgrcv 从消息队列中获取消息，保存到 msg_ptr 所指的空间中去。
    msg_ptr 和 msg_sz 的规则和 msgsnd 一样。

    msg_type 目的是实现一种接收优先级：
    - 如果为0，就获取队列中第一个可用消息
    - 如果大于0，就获取队列中具有相同的 msg_type 的第一个消息
    - 如果小于0，将获取消息类型小于等于 msg_type 的绝对值的第一个消息

    msgflg 用于控制当队列中没有相应类型的消息可以接收时将发生的事情。如果设置了 IPC_NOWAIT ，
    函数就立即返回-1 。若无此标记，进程将挂起等待一条相应的类型的消息到达。

    成功时函数返回接收到缓存区的字节数（不包括开头的 msg_type ），失败返回 -1 。
    成功后消息会从消息队列中删除掉。
*/

#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 1111
static int msgid;

struct msg_st {
    long int msg_type;
    char ch;
};

void msg_send()
{
    printf("Enter some words:\n");

    char ch;
    while (1) {
        ch = getchar();

        struct msg_st data;
        data.msg_type = 666;
        data.ch = ch;
        int res = msgsnd(msgid, &data, 1, 0);
        if (res == -1) {
            fprintf(stderr, "msgsnd failed\n");
            return;
        }
        printf("send - %c\n", ch);

        if (ch == '\n')
            break;
    }
}

void msg_recv()
{
    while (1) {
        struct msg_st data;
        long int nrecv = msgrcv(msgid, &data, 1, 0, 0);
        if (nrecv == -1) {
            fprintf(stderr, "msgrcv failed\n");
            perror("msgrcv");
            return;
        }
        if (data.ch == '\n')
            break;
        printf("recv - size %lu, msg_type %lu, msg_data: %c\n", 
            nrecv, data.msg_type, data.ch);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <send|recv>\n", argv[0]);
        return 1;
    }

    msgid = msgget(KEY, 0666|IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed\n");
        return 1;
    }

    const char* cmd = argv[1];
    if (strcmp(cmd, "send") == 0) {
        msg_send();
    }
    else if (strcmp(cmd, "recv") == 0) {
        msg_recv();
        msgctl(msgid, IPC_RMID, 0);
    }
    else {
        fprintf(stderr, "Usage: %s <send|recv>\n", argv[0]);
        return 1;
    }

    return 0;
}