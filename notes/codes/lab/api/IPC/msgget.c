/*
    #include <sys/msg.h>

    int msgget(key_t key, int msgflg);

    创建或访问一个消息队列，它由 key 索引。 msgflg 由9个权限标志组成，和文件的一样。可以给它添加上
    IPC_CREAT ，那么就会创建消息队列，如果已经存在，也不会有问题。

    成功返回一个正整数的标识符，失败返回-1 。
*/

#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get(key_t key)
{
    int msgid;

    msgid = msgget(key, 0666);
    if (msgid == -1) {
        fprintf(stderr, "msgget(get) failed, key: %d\n", key);
        return;
    }
    
    printf("msgget(get) succ, key: %d\n", key);
}

void create(key_t key)
{
    int msgid;

    msgid = msgget(key, 0666|IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget(create) failed, key: %d\n", key);
        return;
    }
    
    printf("msgget(create) succ, key: %d\n", key);
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <key> <get|create>\n", argv[0]);
        return 1;
    }

    const char* cmd = argv[2];
    key_t key = atoi(argv[1]);
    if (strcmp(cmd, "get") == 0) {
        get(key);
    }
    else if (strcmp(cmd, "create") == 0) {
        create(key);
    }
    else {
        fprintf(stderr, "Usage: %s <get|create>\n", argv[0]);
        return 1;
    }

    return 0;
}