/*
 * #include <sys/resource.h>
 *
 * int getrusage(int who, struct rusage *r_usage);
 *
 * 获取程序当前消耗的 CPU 时间，写入到 r_usage 。
 *
 * 结构 struct rusage 有下面的成员：
 *
 * struct timeval ru_utime			使用的用户时间
 * struct timeval ru_stime			使用的系统时间
 *
 * 结构 struct timeval 有下面的成员：
 *
 * time_t tv_sec					秒（整数）
 * suseconds_t tv_usec;				微秒（整数）
 *
 * who 可以有：
 * RUSAGE_SELF			返回当前程序的使用信息
 * RUSAGE_CHILDREN		返回当前程序加子进程的使用信息
 *
 * 函数成功返回0，失败返回-1 。
 */

#include <sys/resource.h>
#include <stdio.h>

void work()
{
	FILE *f;
	int loop = 0;

	while (loop++ < 100000) {
		f = tmpfile();
		fprintf(f, "wowowowowo\n");
		fclose(f);
	}
}

int main()
{
	work();

	struct rusage r_usage;
	getrusage(RUSAGE_SELF, &r_usage);

	printf("User cost: %ld.%ld\n", r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec);
	printf("System cost: %ld.%ld\n", r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);

	return 0;
}
