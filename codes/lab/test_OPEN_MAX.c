#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_TRY_OPEN_TIMES 10000

/*
 * 测试一个进程同时打开文件描述符的最大数量
 * 测试环境：CentOS 7
 * 结果：可以打开1021个文件
 */

int main()
{
	static int fd_list[MAX_TRY_OPEN_TIMES] = {0};
	char file[256] = {0};

	// create and open tmp file
	int open_count = 0;
	for (; open_count < MAX_TRY_OPEN_TIMES; ++open_count)
	{
		sprintf(file, "test_file_%d", open_count);
		int fd = open(file, O_CREAT, S_IRUSR);
		if (fd == -1)
		{
			perror("open");
			break;
		}
		
		fd_list[open_count] = fd;
	}

	printf("[DEBUG] open_count: %d\n", open_count);

	// close fd
	for (int i = 0; i < open_count && i < MAX_TRY_OPEN_TIMES; ++i)
	{
		close(fd_list[i]);
		fd_list[i] = 0;
	}

	printf("press enter to continue...");
	(void)getchar();

	// delete tmp file
	for (int i = 0; i < open_count && i < MAX_TRY_OPEN_TIMES; ++i)
	{
		sprintf(file, "test_file_%d", i);
		(void)unlink(file);
	}

	return 0;
}
