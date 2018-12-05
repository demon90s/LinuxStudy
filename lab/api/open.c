/*
 * open（p84）
 * open建立了一条到文件或设备的访问路径。
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 例子：打开文件读
 */
void example_openfile_to_read()
{
	int fd;

	fd = open("/tmp/test.txt", O_RDONLY, 0777);
	if (fd == -1) {
		perror("open");
		return;
	}

	printf("open file to read succ\n");

	close(fd);
}

/*
 * 例子：打开文件写
 * 文件如果不存在，打开失败
 */
void example_openfile_to_write()
{
	int fd;

	fd = open("/tmp/test.txt", O_WRONLY, 0777);
	if (fd == -1) {
		perror("open");
		return;
	}

	printf("open file to write succ\n");

	close(fd);
}

/*
 * 例子：打开文件写
 * 文件如果不存在，则创建
 */
void example_openfile_to_write2()
{
	int fd;

	fd = open("/tmp/test.txt", O_WRONLY | O_CREAT, 0777);
	if (fd == -1) {
		perror("open");
		return;
	}

	printf("open file to write2 succ\n");

	close(fd);
}

int main()
{
	//example_openfile_to_read();
	//example_openfile_to_write();
	example_openfile_to_write2();

	exit(EXIT_SUCCESS);
}
