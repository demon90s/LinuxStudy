/*
    #include <sys/msg.h>

    int msgctl(int msgid, int command, struct msqid_ds *buf);

    与共享内存的控制函数非常相似。结构 msgqid_ds 至少包含：

    struct msgqid_ds {
        uid_t msg_perm.uid;
        uid_t msg_perm.gid;
        mode_t msg_perm.mode;
    };

    command 可以有：
    - IPC_STAT 把消息队列当前的信息写入 buf
    - IPC_SET 如果进程有足够的权限，则把 buf 设置为当前消息队列的相关值
    - IPC_RMID 删除消息队列

    函数成功返回0 ，失败返回-1 。
    如果删除消息队列时，某个进程正在 msgsnd 或 msgrcv 函数中等待，这两个函数将失败。
*/

#include <sys/msg.h>
#include <stdio.h>

#define KEY 1234

int main(int argc, char *argv[])
{
    int msgid;
    msgid = msgget(KEY, 0666|IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed\n");
        return 1;
    }

    int res;
    res = msgctl(msgid, IPC_RMID, 0);
    if (res == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        return 1;
    }
    printf("msgctl(IPC_RMID) succ\n");
    
    return 0;
}
