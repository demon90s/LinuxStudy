/*
	#include <sys/types.h>
	#include <sys/stat.h>
	int mkfifo(const char* filename, mode_t mode);
	创建一个命名管道文件。成功返回0，否则非零。
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int res = mkfifo("/tmp/my_fifo", 0777);
	if (res == 0) printf("FIFO created\n");
	else {
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
