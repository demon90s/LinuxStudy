/*
 * #include <unistd.h>
 * int isatty(int fd);
 *
 * 判断 fd 关联的文件是否连接到一个终端，如果是返回1，否则返回0 。
 */

#include <unistd.h>
#include <stdio.h>

int main()
{
	if (!isatty(1)) {
		fprintf(stderr, "Standard output is not connect to a tty!\n");
		return 1;
	}

	printf("Standard output is connect to a tty");

	return 0;
}
