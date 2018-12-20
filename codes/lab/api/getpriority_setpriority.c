/*
 * #include <sys/resource.h>
 *
 * int getpriority(int which, id_t who);
 * int setpriority(int which, id_t who, int priority);
 *
 * 获取/设置进程的优先级 priority ，其取值范围是 -20 ~ 20
 *
 * which 与 who 成对出现，如下：
 *
 * which			who
 * PRIO_PROCESS		进程标识符
 * PRIO_PGRP		进程组
 * PRIO_USER		用户标识符
 *
 * priority 默认为0，越高，则优先级越低。
 *
 * getpriority 成功时返回一个有效的优先级，失败返回-1并设置 errno ，-1是一个有效的优先级，因此要通过 errno 检查错误。
 *
 * setpriority 成功返回0，否则返回-1 。
 */

#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	int priority;

	errno = 0;
	priority = getpriority(PRIO_PROCESS, getpid());
	if (errno == 0) {
		printf("priority: %d\n", priority);
	}

	setpriority(PRIO_PROCESS, getpid(), -10);

	errno = 0;
	priority = getpriority(PRIO_PROCESS, getpid());
	if (errno == 0) {
		printf("priority: %d\n", priority);
	}

	return 0;
}
