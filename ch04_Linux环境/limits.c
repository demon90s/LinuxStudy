/*
 * 实验 资源限制
 */

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 产生一些 CPU 负载
void work()
{
	FILE *f;
	int i;
	double x = 4.5;

	f = tmpfile();
	for (i = 0; i < 1000000; i++) {
		fprintf(f, "Do some input\n");
		if (ferror(f)) {
			fprintf(stderr, "Error writing to temprory file\n");
			exit(1);
		}
	}

	for (i = 0; i < 10000000; i++)
		x = log(x*x + 3.21);
}

int main()
{
	struct rusage r_usage;
	struct rlimit r_limit;
	int priority;

	// 使用 getrusage 发现 work 调用的 CPU 时间
	work();
	getrusage(RUSAGE_SELF, &r_usage);

	printf("CPU usage: User = %ld.%06ld, System = %ld.%06ld\n",
		r_usage.ru_utime.tv_sec, r_usage.ru_utime.tv_usec,
		r_usage.ru_stime.tv_sec, r_usage.ru_stime.tv_usec);

	// 调用 getpriority 和 getrlimit 来发现它的当前优先级和文件大小限制
	priority = getpriority(PRIO_PROCESS, getpid());
	printf("Current priority = %d\n", priority);

	getrlimit(RLIMIT_FSIZE, &r_limit);
	printf("Current FSIZE limit: soft= %ld, hard = %ld\n",
		r_limit.rlim_cur, r_limit.rlim_max);

	// 调用 setrlimit 设置文件大小限制并再次 work ，这次 work 会失败，因为它创建不了那么大的文件
	r_limit.rlim_cur = 2048;
	r_limit.rlim_max = 4096;
	printf("Setting a 2K file size limit\n");
	setrlimit(RLIMIT_FSIZE, &r_limit);

	work();

	return 0;
}
