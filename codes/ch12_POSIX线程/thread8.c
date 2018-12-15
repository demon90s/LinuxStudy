/*
 * 多线程（p438）
 */

// PS: 按照书本上的例子，以下的代码在我的机器上会报warning。

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 6

void* thread_func(void *arg);

int main(int argc, char* argv[])
{
	int res;
	pthread_t a_thread[NUM_THREADS];
	void *thread_result;
	int lots_of_thread;

	for (lots_of_thread = 0; lots_of_thread < NUM_THREADS; ++lots_of_thread)
	{
		res = pthread_create(&a_thread[lots_of_thread], NULL, thread_func, (void*)lots_of_thread);
		if (res != 0)
		{
			perror("Thread create failed");
			exit(EXIT_FAILURE);
		}
		//sleep(1);
	}
	printf("Waiting for thread to finish...\n");
	for (lots_of_thread = NUM_THREADS - 1; lots_of_thread >= 0; --lots_of_thread)
	{
		res = pthread_join(a_thread[lots_of_thread], &thread_result);
		if (res != 0)
		{
			perror("Thread join failed");
		}
		else
		{
			printf("Picked up a thread\n");
		}
	}

	printf("All done\n");

	exit(0);
}

void *thread_func(void *arg)
{
	int my_number = (int)arg;
	int rand_num;

	printf("thread function is running, Arguments was %d\n", my_number);
	rand_num = 1 + (9.0 * rand() / (RAND_MAX + 1.0));
	sleep(rand_num);
	printf("Bye from: %d\n", my_number);
	pthread_exit(NULL);
}
