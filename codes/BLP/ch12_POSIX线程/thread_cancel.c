/*
 * 取消一个线程（p436）
 * 
 * #include <pthread.h>
 * int pthread_cancel(pthread_t thread);
 * 给线程发送一个取消请求, 线程可以选择接受或忽略. 线程接受后会选择一个时机终止.
 * 
 * 线程选择接受或忽略由下面接口设定:
 * int pthread_setcancelstate(int state, int *oldstate);
 * state 取值有:
 * PTHREAD_CANCEL_ENABLE 表示接受取消请求, 是默认选项
 * PTHREAD_CANCEL_DISABLE 表示忽略取消请求
 * 
 * 当接受了取消请求后, 线程由下面的接口选择取消时机:
 * int pthread_setcanceltype(int type, int *oldtype);
 * type 取值有:
 * PTHREAD_CANCEL_DEFERRED 是默认选项, 表示挂起线程, 并等待请求的线程执行了某个特定函数后结束, 比如 pthread_join
 * PTHREAD_CANCEL_ASYNCHRONOUS 表示立刻采取行动 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* thread_function(void *arg);

int main(int argc, char* argv[])
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	sleep(3);
	printf("Cancling thread...\n");
	res = pthread_cancel(a_thread);
	if (res != 0)
	{
		perror("Thread cancelation failed");
		exit(EXIT_FAILURE);
	}

	printf("Waiting for thread to finish...\n");

	res = pthread_join(a_thread, &thread_result);
	if (res != 0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Thread joined.\n");

	exit(0);
}

void* thread_function(void *arg)
{
	int i, res = 0;

	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	// 默认就是 ENABLE 的
	//res = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); // 此选项忽略掉取消请求
	if (res != 0)
	{
		perror("Thread pthread_setcancelstate failed");
		exit(EXIT_FAILURE);
	}

	res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);	// 默认类型就是 DEFERRED
	if (res != 0)
	{
		perror("Thread pthread_setcanceltype failed");
		exit(EXIT_FAILURE);
	}
	printf("thread_function is running\n");
	for (i = 0; i < 10; ++i)
	{
		printf("Thread is still running(%d)...\n", i);
		sleep(1);
	}
	pthread_exit(0);
}
