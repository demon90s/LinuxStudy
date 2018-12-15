/*
 * #include <sys/types.h>
 * #include <sys/stat.h>
 * #include <fcntl.h>
 *
 * int open(const char *pathname, int flags);
 * int open(const char *pathname, int flags, mode_t mode);
 *
 * 打开文件 pathname
 *
 * open 建立了一条到文件或设备的访问路径。
 * open 操作是原子操作。
 *
 * 函数成功返回一个文件描述符，失败返回-1 。
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
	//example_openfile_to_read();
	//example_openfile_to_write();
	//example_openfile_to_write2();
	example_create_lock_file();

	exit(EXIT_SUCCESS);
}
