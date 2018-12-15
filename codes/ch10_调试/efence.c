// 实验：ElectricFence
// 加入链接选项 -lefence 测试

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *ptr = (char*) malloc(1024);
	ptr[0] = 0;

	/* Now write beyond the block */
	ptr[1024] = 0;

	exit(0);
}
