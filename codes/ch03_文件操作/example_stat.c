/*
 * 一个简单的使用stat的例子（见p90），稍微做了点修改
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	struct stat statbuf;
	mode_t modes;

	stat("example_stat.c", &statbuf);
	modes = statbuf.st_mode;

	// 测试是否是普通文件，并且设置了属主的写权限
	if (S_ISREG(modes) && (modes & S_IRWXU)) {
		printf("example_stat.c is a regular file\n");
	}

	exit(0);
}
