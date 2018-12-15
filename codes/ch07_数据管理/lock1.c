// 实验：创建锁文件

// 第一次运行程序会成功创建锁文件，第二次将失败（除非把锁文件删除）

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	int file_desc;
	int save_errno;

	file_desc = open("/tmp/LCK.test", O_RDWR | O_CREAT | O_EXCL, 0444);
	if (file_desc == -1) {
		save_errno = errno;
		printf("Open failed with error %d\n", save_errno);
	}
	else {
		printf("Open succeeded\n");
	}
	exit(EXIT_SUCCESS);
}
