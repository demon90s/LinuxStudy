// 实验：打开 FIFO 文件


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"

int main(int argc, char *argv[])
{
	int res;
	int open_mode;
	int i;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <some combination of O_RDONLY O_WRONLY O_NONBLOCK>\n", *argv);
		exit(EXIT_FAILURE);
	}

	/* 假设程序已通过测试，现在我们根据命令行参数来设置 open_mode 的值 */
	for (i = 1; i < argc; i++) {
		if (strncmp(*++argv, "O_RDONLY", 8) == 0)
			open_mode |= O_RDONLY;

		if (strncmp(*argv, "O_WRONLY", 8) == 0)
			open_mode |= O_WRONLY;

		if (strncmp(*argv, "O_NONBLOCK", 10) == 0)
			open_mode |= O_NONBLOCK;
	}

	/* 现在检查 FIFO 文件是否存在，如有必要就创建它，接下来打开这个 FIFO 文件并输出相应的信息
	 * 然后程序小憩一下。最后，关闭 FIFO。 
	 */
	if (access(FIFO_NAME, F_OK) == -1) {
		res = mkfifo(FIFO_NAME, 0777);
		if (res != 0) {
			fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	printf("Process %d opening FIFO\n", getpid());
	res = open(FIFO_NAME, open_mode);
	printf("Process %d finished result %d\n", getpid(), res);
	sleep(5);
	if (res != -1) (void)close(res);
	printf("Process %d finished\n", getpid());

	exit(EXIT_SUCCESS);
}
