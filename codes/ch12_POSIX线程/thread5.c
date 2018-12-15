/*
 * 设置脱离状态属性（p412）
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
