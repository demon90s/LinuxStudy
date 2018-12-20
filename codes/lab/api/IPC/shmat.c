/*
    #include <sys/shm.h>

    void *shmat(int shm_id, const void *shm_addr, int shmflg);

    将由 shm_id 标示的共享内存连接到进程。

    shm_addr 指定共享内存连接到当前进程中的地址位置，它通常是一个空指针，表示让系统来选择共享内存出现的地址。

    shmflg 有两个可能的取值是 SHM_RND (控制共享内存的连接地址)和 SHM_RDONLY （使得连接的内存只读）。
    很少使用 SHM_RND 。

    shmat 返回共享内存第一个字节的指针，如果失败，它就返回-1 。
*/

#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KEY 1234

struct shared_block {
    int id;
    char name[32];
};

void write_shm()
{
    // get shared memory
    int shm_id;
    shm_id = shmget(KEY, sizeof(struct shared_block), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        fprintf(stderr, "shmget failed\n");
        return;
    }

    // connect shared memory
    void* shm_ptr;
    struct shared_block *sb_ptr;
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void*)-1) {
        fprintf(stderr, "shmat failed\n");
        return;
    }
    sb_ptr = (struct shared_block*)shm_ptr;

    // write
    sb_ptr->id = 100;
    strcpy(sb_ptr->name, "hello");
    printf("write - {%d %s}\n", sb_ptr->id, sb_ptr->name);
}

void read_shm()
{
    // get shared memory
    int shm_id;
    shm_id = shmget(KEY, sizeof(struct shared_block), 0666);
    if (shm_id == -1) {
        fprintf(stderr, "shmget failed\n");
        return;
    }

    // connect shared memory
    void* shm_ptr;
    shm_ptr = shmat(shm_id, NULL, SHM_RDONLY);
    if (shm_ptr == (void*)-1) {
        fprintf(stderr, "shmat failed\n");
        return;
    }

    // read
    struct shared_block sb;
    memcpy(&sb, shm_ptr, sizeof(sb));
    printf("read - {%d %s}\n", sb.id, sb.name);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <write|read>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "write") == 0)
        write_shm();
    else if (strcmp(argv[1], "read") == 0)
        read_shm();
    else {
        fprintf(stderr, "Usage: %s <write|read>\n", argv[0]);
        return 1;
    }

    return 0;
}