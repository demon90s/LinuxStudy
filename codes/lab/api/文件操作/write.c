/*
 * write （p82）
 * write的作用是把缓冲区 buf 的前 nbytes 个字节写入与文件描述符 fildes 关联的文件中。
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 例子，写一些内容到文件
 */
void example_write_to_file()
{
	int fd;
	int nwrite;
	const char* buf = "Hello Linux";

	fd = open("/tmp/test.txt", O_WRONLY | O_CREAT, 0777);
	if (fd == -1) {
		perror("open");
		return;
	}

	nwrite = write(fd, buf, strlen(buf));
	if (nwrite == -1) {
		perror("write");
	}
	else {
		printf("write %d bytes\n", nwrite);
	}

	close(fd);
}

int main()
{
	example_write_to_file();

	return 0;
}
