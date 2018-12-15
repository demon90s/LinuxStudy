/*
 * #include <unistd.h>
 * int gethostname(char *name, size_t namelen);
 *
 * 获取机器的网络名，写入长度为 namelen 的数组 name ，成功返回0 ，否则返回-1 。
 */

#include <unistd.h>
#include <stdio.h>

#define NAME_LEN 255

int main()
{
	char name[NAME_LEN + 1];

	if (gethostname(name, NAME_LEN) == 0) {
		printf("hostname: %s\n", name);
	}

	return 0;
}
