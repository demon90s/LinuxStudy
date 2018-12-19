/*
    #include <sys/shm.h>

    int shmdt(const void* shm_addr);
    int shmctl(int shm_id, int cmd, struct shmid_ds *buf);

    shmdt 将共享内存（由　shm_addr 连接）从当前进程中分离，成功返回0，失败返回-1 。
    分离并不意味着删除，只是使得该共享内存对当前进程不再可用。

    shmctl 可以获取/设置共享内存的权限、还可以删除共享内存。
    command 可以取值：
    IPC_STAT - 获取权限信息
    IPC_SET - 设置权限信息
    IPC_RMID - 删除共享内存段

    shmid_ds 结构至少有：
    struct shmid_ds {
        uid_t shm_perm.uid;
        uid_t shm_perm.gid;
        mode_t shm_perm.mode;
    };

    函数成功返回0，失败返回-1 。
*/

#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KEY 1234

struct block
{
    int id;
    char name[32];
};

void test1()
{
    int shm_id;

    shm_id = shmget(KEY, sizeof(struct block), 0666|IPC_CREAT);
    if (shm_id == -1) {
        fprintf(stderr, "shmget failed\n");
        return;
    }

    void *shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void*)-1) {
        fprintf(stderr, "shmat failed\n");
        return;
    }

    int res = shmdt(shm_ptr);
    if (res == -1) {
        fprintf(stderr, "shmdt failed\n");
        return;
    }
    else {
        printf("shmdt succ\n");
    }


    res = shmctl(shm_id, IPC_RMID, 0);
    if (res == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        return;
    }
    else {
        printf("shmctl(IPC_RMID) succ\n");
    }
}

int main()
{
    test1();

    return 0;
}