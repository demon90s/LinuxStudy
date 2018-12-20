#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * 例子：创建锁文件
 * 如果锁文件已存在，那么创建失败
 */
void example_create_lock_file()
{
	int fd;

	fd = open("/tmp/LCK.test", O_RDWR | O_CREAT | O_EXCL, 0444);
	if (fd == -1) {
		perror("Create lock file failed");
	}
	else {
		printf("Create lock file success\n");
	}
}

int main()
{
	example_create_lock_file();
}
