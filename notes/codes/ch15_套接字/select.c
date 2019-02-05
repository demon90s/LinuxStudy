/*
	select 系统调用

	#include <sys/time.h>
	#include <sys/types.h>

	int select(int nfds, fd_set *readfds, fd_set *writefds,
					fd_set *exceptfds, struct timeval *timeout);

	阻塞地测试 readfds、writefds、exceptfds 中，是否有一个文件描述符已处于可读、可写、出错状态。

	nfds 表示测试的描述符最大nfds范围。

	三个 fd_set 可以是空指针，表示不测试。

	如果 timeout 表示阻塞超时时间，若不为空，则经过了设定的时间后调用返回0 。

	如果描述符内容有变化，则立刻返回发生变化的描述符数量。失败时返回-1 。

	PS：timeout 在返回时可能会被修改成剩余的时间。
*/

#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

void test1()
{
	char buffer[128];
	int result, nread;

	fd_set inputs, testfds;
	struct timeval timeout;

	// 对inputs进行初始化以处理来自键盘的输入
	FD_ZERO(&inputs);
	FD_SET(STDIN_FILENO, &inputs);

	printf("[DEBUG] FD_SETSIZE: %d\n", FD_SETSIZE); // 1024 on Ubuntu 18.04

	// 在标准输入stdin上最多等待输入2.5秒
	while (1) {
		testfds = inputs;
		timeout.tv_sec = 2;
		timeout.tv_usec = 500000;

		result = select(STDIN_FILENO + 1, &testfds, NULL, NULL, &timeout);

		// 经过这段时间之后，对result进行测试。如果没有输入，程序将再次循环。
		// 如果出现一个错误，程序将退出运行
		switch(result) {
			case 0:
				printf("timeout\n");
				break;
			case -1:
				perror("select");
				exit(1);
			default:
				printf("[DEBUG] select returned %d\n", result);
				if (FD_ISSET(STDIN_FILENO, &testfds)) {
					ioctl(STDIN_FILENO, FIONREAD, &nread);
					if (nread == 0) {
						printf("keyboard done\n");
						exit(0);
					}
					nread = read(STDIN_FILENO, buffer, nread);
					buffer[nread] = 0;
					printf("read %d from keyboard: %s", nread, buffer);
				}
				break;
		}
	}
}

int main()
{
	test1();

	exit(EXIT_SUCCESS);
}
