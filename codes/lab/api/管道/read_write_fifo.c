/*
	读写 FIFO 

	如果 FIFO 是阻塞的读写，那么：
	对于 read ，将等待直到有数据可读。
	对于 write ，如果 FIFO 已经满了，调用将等待，直到有数据可以写。

	建议每次写入的数据块都不超过 PIPE_BUF 字节。这样系统就可以确保数据块
	不会交错在一起。
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define FIFO_FILE "/tmp/test_fifo"

void read_proc()
{
	int fd;

	printf("read_proc begin\n");
	fd = open(FIFO_FILE, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return;
	}

	// read chars
	{
		char ch;
		while (read(fd, &ch, 1) == 1) {
			printf("read - %c\n", ch);
		}
	}

	printf("read_proc end\n");
}

void write_proc()
{
	int fd;

	printf("write_proc begin\n");

	fd = open(FIFO_FILE, O_WRONLY);
	if (fd == -1) {
		perror("fd");
		return;
	}

	// write some chars
	{
		char ch;
		printf("Input some words: ");
		while ((ch = getchar()) != EOF) {
			if (ch != '\n')
				write(fd, &ch, 1);
		}
	}

	printf("write_proc end\n");
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <read|write>\n", argv[0]);
		return 1;
	}

	if (access(FIFO_FILE, F_OK) == -1) {
		mkfifo(FIFO_FILE, 0777);
	}

	if (strcmp(argv[1], "read") == 0)
		read_proc();
	else if (strcmp(argv[1], "write") == 0)
		write_proc();
	else {
		fprintf(stderr, "Usage: %s <read|write>\n", argv[0]);
		return 1;
	}

	return 0;
}
