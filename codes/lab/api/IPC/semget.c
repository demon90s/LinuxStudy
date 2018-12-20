/*
	#include <sys/sem.h>
	int semget(key_t key, int num_sems, int sem_flags);

	semget 创建一个新信号量或取得一个已有信号量。
	key 是整数，不相关的进程可以通过它访问同一个信号量。
	函数返回信号量标示符（正数），它是信号量操作函数的句柄。失败返回-1 。

	num_sems 参数指定需要的信号量数目，它几乎总是为1 。

	sem_flags 参数是一组标志，低端的9个比特是信号量权限，类似文件访问权限。
	可设置 IPC_CREAT ,即使 key 已存在，也不会产生错误。
	使用 IPC_CREAT | IPC_EXCL 来确保创建出的是一个新的、唯一的信号量。此时如果信号量已存在，它将返回一个错误。

	my note:
		如果程序不删除信号量，那么它将在系统中存在，即使没有程序使用它也是如此。
*/

#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 创建唯一的信号量，如果信号量在系统中存在，那么将失败
void create_semaphore(key_t key)
{
	int sem_id = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL);
	if (sem_id == -1) {
		fprintf(stderr, "Create semaphore failed\n");
		return;
	}
	printf("Create semaphore succ, sem_id: %d\n", sem_id);
}

// 获取信号量
void get_semaphore(key_t key)
{
	int sem_id = semget(key, 1, 0666);
	if (sem_id == -1) {
		fprintf(stderr, "Get semaphore failed\n");
		return;
	}
	printf("Get semaphore succ, sem_id: %d\n", sem_id);
}

// 通过命令行参数抓取 key
int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <create|get> <sem_key>\n", argv[0]);
		return 1;
	}

	{
		const char* cmd = argv[1];
		key_t key = atoi(argv[2]);

		if (strcmp(cmd, "create") == 0)
			create_semaphore(key);
		else if (strcmp(cmd, "get") == 0)
			get_semaphore(key);
		else
			fprintf(stderr, "Usage: %s <create|get> <sem_key>\n", argv[0]);
	}

	return 0;
}
