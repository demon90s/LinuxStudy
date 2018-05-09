/*
 * 发送信号（p408）
 */

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig)
{
	alarm_fired = 1;
}

int main(int argc, char* argv[])
{
	pid_t pid;

	printf("alarm application starting\n");

	pid = fork();
	switch (pid) {
	case -1:
		perror("fork failed");
		exit(1);
	case 0:
		// 等待5秒后，发送一个SIGALRM信号给它的父进程
		sleep(5);
		kill(getppid(), SIGALRM);
		exit(0);
	}

	/* if we get here we are the parent process */
	printf("waiting for alarm to go off\n");
	(void) signal(SIGALRM, ding);

	pause();
	if (alarm_fired)
		printf("Ding!\n");

	printf("done\n");

	exit(0);
}
