/*
	可选的打开标志有：

	- O_RDONLY ： open 将阻塞，除非有一个进程以写方式打开同一个 FIFO
	
	- O_RDONLY|O_NONBLOCK ：将成功并立刻返回

	- O_WRONLY ： open 将阻塞，直到有一个进程以读方式打开同一个 FIFO 为止

	- O_WRONLY|O_NONBLOCK ： 总是立刻返回，如果没有进程以读方式打开 FIFO ，open 将返回一个错误 -1 ， FIFO 也不会被打开。
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define FIFO_FILE "/tmp/test_fifo"

void rd()
{
	int fd;

	printf("Open with flag O_RDONLY begin\n");
	fd = open(FIFO_FILE, O_RDONLY);
	if (fd == -1) {
		perror("Open with flag O_RDONLY failed");
		return;
	}
	printf("Open with flag O_RDONLY returned, fd: %d\n", fd);
}

void rdnb()
{
	int fd;

	printf("Open with flag O_RDONLY|O_NONBLOCK begin\n");
	fd = open(FIFO_FILE, O_RDONLY|O_NONBLOCK);
	if (fd == -1) {
		perror("Open with flag O_RDONLY|NONBLOCK failed");
		return;
	}
	printf("Open with flag O_RDONLY|NONBLOCK returned, fd: %d\n", fd);
}

void wr()
{
	int fd;

	printf("Open with flag O_WRONLY begin\n");
	fd = open(FIFO_FILE, O_WRONLY);
	if (fd == -1) {
		perror("Open with flag O_WRONLY failed");
		return;
	}
	printf("Open with flag O_WRONLY returned, fd: %d\n", fd);
}

void wrnb()
{
	int fd;

	printf("Open with flag O_WRONLY|O_NONBLOCK begin\n");
	fd = open(FIFO_FILE, O_WRONLY|O_NONBLOCK);
	if (fd == -1) {
		perror("Open with flag O_WRONLY|O_NONBLOCK failed");
		return;
	}
	printf("Open with flag O_WRONLY|O_NONBLOCK returned, fd: %d\n", fd);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <rd|rdnb|wr|wrnb>\n", argv[0]);
		return 1;
	}

	if (access(FIFO_FILE, F_OK) == -1) {
		printf("create fifo\n");
		mkfifo(FIFO_FILE, 0777);
	}

	{
		char *cmd = argv[1];
		if (strcmp(cmd, "rd") == 0) {
			rd();
		}
		else if (strcmp(cmd, "rdnb") == 0) {
			rdnb();
		}
		else if (strcmp(cmd, "wr") == 0) {
			wr();
		}
		else if (strcmp(cmd, "wrnb") == 0) {
			wrnb();
		}
		else {
			fprintf(stderr, "Usage: %s <rd|rdnb|wr|wrnb>\n", argv[0]);
			return 1;
		}
	}

	return 0;
}
