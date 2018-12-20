/*
    #include <sys/shm.h>

    int shmget(key_t key, size_t size, int shmflg);

    创建/获取共享内存的函数。 key 为共享内存段命名，函数返回一个共享内存标示符，用于后续的函数。
    size　表示共享内存的容量。
    shmflg 有9个比特的权限标志，其作用和文件的权限标志一样。 IPC_CREAT 标志表示创建一个共享内存，如果无需用到它，也不会有错误。

    成功函数返回一个非负整数，即共享内存标示符，如果失败，返回-1 。
*/

#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct shared_block {
    int id;
    char name[32];
};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <get|create> <key>\n", argv[0]);
        return 1;
    }

    key_t key;
    int shm_id;
    int shmflg = 0666;

    key = atoi(argv[2]);
    
    if (strcmp(argv[1], "create") == 0)
        shmflg |= IPC_CREAT; 
    
    shm_id = shmget(key, sizeof(struct shared_block), shmflg);
    if (shm_id == -1) {
        fprintf(stderr, "shmget failed\n");
        return 2;
    }
    else
    {
        printf("shmget succ, shm_id: %d\n", shm_id);
    }
    
    return 0;
}