// example: execlp函数（p397）

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Running ps with execlp\n");
	execlp("ps", "ps", "ax", NULL);
	printf("Done.\n");	// 不会被执行

	exit(0);
}
