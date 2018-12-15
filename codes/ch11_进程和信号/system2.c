// example: system函数（p394）

#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Running ps with system\n");
	system("ps ax &"); // 由于在后台运行，所以ps程序一启动shell就返回了
	printf("Done.\n");

	exit(0);
}
