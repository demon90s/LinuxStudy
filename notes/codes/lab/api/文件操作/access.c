/*
	#include <unistd.h>
	int access(const char* pathname, int mode);

	测试用户对文件 pathname 的访问权限 mode 。

	mode 可取值 F_OK ,代表判断文件是否存在。

	或取 mask 值：
	R_OK 是否有 read 权限
	W_OK 是否有 write 权限
	X_OK 是否有 execute 权限

	如果有如此的权限，返回0 ，返回-1 表示没有权限或出现了其他的错误，
	errno 被设置。
*/

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	const char* pathname = argv[0];

	printf("Test file: %s\n", pathname);

	if (access(pathname, F_OK) == 0) {
		printf("Check F_OK: file is exist\n");
	}
	else {
		printf("Check F_OK: file is not exist\n");
	}

	if (access(pathname, R_OK) == 0) {
		printf("Check R_OK: file can read\n");
	}
	else {
		printf("Check R_OK: file can not read\n");
	}

	if (access(pathname, W_OK) == 0) {
		printf("Check W_OK: file can write\n");
	}
	else {
		printf("Check W_OK: file can not write\n");
	}

	if (access(pathname, X_OK) == 0) {
		printf("Check X_OK: file can execute\n");
	}
	else {
		printf("Check X_OK: file can not execute\n");
	}

	return 0;
}
