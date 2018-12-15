/*
 * 一个线程信号量（p424）
 * 一个细微错误的例子，由于增加了多次信号量导致字符统计线程反复统计多次
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void* thread_function(void *arg);
sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main(int argc, char* argv[])
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = sem_init(&bin_sem, 0, 0);
	if (res != 0) {
		perror("Semaphore initialization failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0) {
		perror("Thread create failed");
		exit(EXIT_FAILURE);
	}

	printf("Input some text, Enter 'end' to finish\n");
	while (strncmp("end", work_area, 3) != 0) {
		if (strncmp("FAST", work_area, 4) == 0) { // 出于演示目的而人为制造的问题
			sem_post(&bin_sem);
			strcpy(work_area, "Wheeee...");
		}
		else {
			fgets(work_area, WORK_SIZE, stdin);
		}
		sem_post(&bin_sem);
	}
	printf("\nWaiting for thread to finish...\n");

	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined\n");

	sem_destroy(&bin_sem);

	exit(0);
}

void *thread_function(void *arg)
{
	sem_wait(&bin_sem);
	while (strncmp("end", work_area, 3) != 0) {
		printf("You input %lu characters: %s\n", strlen(work_area) - 1, work_area);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}
