/*
 * 调度（p434）
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "Hello World";
int thread_finish = 0;

int main(int argc, char* argv[])
{
	int res;
	pthread_t a_thread;
	pthread_attr_t thread_attr;

	// 调度相关变量
	int max_priority;
	int min_priority;
	struct sched_param scheduling_value;
	//---------------------------------

	res = pthread_attr_init(&thread_attr);
	if (res != 0) {
		perror("Atrribute creation failed");
		exit(1);
	}

	res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	if (res != 0)
	{
		perror("Setting detached attribute failed");
		exit(1);
	}

	// 设置调度属性
	res = pthread_attr_setschedpolicy(&thread_attr, SCHED_OTHER);
	if (res != 0)
	{
		perror("Setting policy failed");
		exit(EXIT_FAILURE);
	}

	// 查找允许的优先级范围
	max_priority = sched_get_priority_max(SCHED_OTHER); (void)max_priority;
	min_priority = sched_get_priority_min(SCHED_OTHER);

	// 然后设置优先级
	scheduling_value.sched_priority = min_priority;
	res = pthread_attr_setschedparam(&thread_attr, &scheduling_value);
	if (res != 0)
	{
		perror("Setting scheduling priority failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_create(&a_thread, &thread_attr, thread_function, (void*)message);
	if (res != 0)
	{
		perror("Thread create failed");
		exit(1);
	}
	(void)pthread_attr_destroy(&thread_attr);

	while (!thread_finish) {
		printf("Waiting for thread to say it's finished...\n");
		sleep(1);
	}
	printf("Other thread finished, bye\n");

	exit(0);
}

void* thread_function(void *arg)
{
	printf("thread function is running. Argument was %s\n", (char*)arg);
	sleep(4);
	printf("second thread setting finished flag, and exiting now\n");
	thread_finish = 1;
	pthread_exit(NULL);
}
