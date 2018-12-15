/*
 * 信号处理（p406）
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL);
}

int main(int argc, char* argv[])
{
	(void) signal(SIGINT, ouch);

	while (1) {
		printf("Hello World!\n");
		sleep(1);
	}

	exit(0);
}
