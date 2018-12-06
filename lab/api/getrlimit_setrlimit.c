/*
 * #include <sys/resource.h>
 *
 * int getrlimit(int resource, struct rlimit *r_limit);
 * int setlimit(int resource, const struct rlimit *r_limit);
 *
 * 获取/设置系统资源的限制
 *
 * r_limit 是一对数值：
 * rlim_t rlim_cur			软限制（一个建议性限制）
 * rlim_t rlim_max			硬限制（超过后可能导致程序终止）
 *
 * rlim_t 是一个整数类型(long int)。
 *
 * 可以限制的资源由 resource 说明，它可以是：
 * RLIMIT_CORE				内核转储文件的大小限制（字节单位）
 * RLIMIT_CPU				CPU 时间限制（以秒为单位）
 * RLIMIT_DATA				数据段限制（以字节为单位）
 * RLIMIT_FSIZE				文件大小限制（以字节为单位）
 * RLIMIT_NOFILE			可以打开的文件数限制
 * RLIMIT_STACK				栈大小限制（以字节为单位）
 * RLIMIT_AS				地址空间（栈和数据）限制（以字节为单位）
 *
 * 函数成功返回0 ，失败返回-1 。
 */

#include <sys/resource.h>
#include <stdio.h>

int main()
{
	struct rlimit stack_limit;
	
	getrlimit(RLIMIT_STACK, &stack_limit);
	printf("Stack Limit: %ld(cur), %ld(max)\n", stack_limit.rlim_cur, stack_limit.rlim_max);

	
	stack_limit.rlim_cur = 20 * 1024 * 1024;
	if (setrlimit(RLIMIT_STACK, &stack_limit) != 0) {
		perror("setrlimit");
		return 1;
	}
	

	getrlimit(RLIMIT_STACK, &stack_limit);
	printf("Stack Limit: %ld(cur), %ld(max)\n", stack_limit.rlim_cur, stack_limit.rlim_max);

	
	return 0;
}
