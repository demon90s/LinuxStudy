#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buffer[128];
	int result, nread;

	fd_set inputs, testfds;
	struct timeval timeout;

	// 对inputs进行初始化以处理来自键盘的输入
	FD_ZERO(&inputs);
	FD_SET(0, &inputs);

	printf("[DEBUG] FD_SETSIZE: %d\n", FD_SETSIZE);

	// 在标准输入stdin上最多等待输入2.5秒
	while (1) {
		testfds = inputs;
		timeout.tv_sec = 2;
		timeout.tv_usec = 500000;

		result = select(FD_SETSIZE, &testfds, NULL, NULL, &timeout);

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
				if (FD_ISSET(0, &testfds)) {
					ioctl(0, FIONREAD, &nread);
					if (nread == 0) {
						printf("keyboard done\n");
						exit(0);
					}
					nread = read(0, buffer, nread);
					buffer[nread] = 0;
					printf("read %d from keyboard: %s", nread, buffer);
				}
				break;
		}
	}

	exit(EXIT_SUCCESS);
}
