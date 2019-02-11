/*
 * write （p82）
 * 
 * #include <unistd.h>
 * ssize_t write(int fd, const void *buf, size_t count);
 * 
 * write的作用是把缓冲区 buf 的前 nbytes 个字节写入与文件描述符 fildes 关联的文件中。
 * 失败返回-1并设置 errno 。
 * 返回实际写入的字节数，由于系统的限制，可能会少于 count 。
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

/*
 * 例子，写比较大的字节数量，测试一次 write 不能写完的情况
 * 在 Ubuntu18.04 上面测试，一次可以写至少 4MB 的数据
 */
void example_write2()
{
	int fd;
	int nwrite;

	fd = open("/tmp/test.txt", O_WRONLY | O_CREAT, 0777);
	if (fd == -1) {
		perror("open");
		return;
	}

	char buf[1024 * 1024 * 4] = "Fuck.....\n";

	nwrite = write(fd, buf, sizeof(buf));

	printf("Write %d bytes, total buf size is: %lu\n", nwrite, sizeof(buf));
}

int main()
{
	//example_write_to_file();
	example_write2();

	return 0;
}
