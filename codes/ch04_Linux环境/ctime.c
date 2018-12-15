// 实验：ctime函数
// 获取一种更友好的时间表示


#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	time_t timeval;

	(void)time(&timeval);
	printf("The date is: %s\n", ctime(&timeval));

	exit(0);
}
