/*
 * wait函数
 * 
 * #include <sys/wait.h>
 * 
 * pid_t wait(int *statloc);
 * 函数成功返回进程ID，出错返回0或-1
 * 
 * 调用 wait 会发生：
 * - 如果进程的所有子进程都在运行，则阻塞
 * - 如果一个子进程已经终止，正等待父进程获取其终止状态，则取得子进程的终止状态后立即返回
 * - 如果进程没有任何子进程，则立即出错返回
 * 
 * statloc 如果不为空，则得到终止进程的终止状态，使用定义好的宏来测试这种状态：
 * - WIFEXITSTED 如果正常终止，则为真，从而可继续用 WEXITSTATUS 获取子进程的退出码
 * - WIFSIGNALED 异常终止则为真，从而可继续用 WTERMSIG 获取使其终止的信号编号，另有些实现可用 WCOREDUMP 判断是否产生了 core 文件
 * - WIFSTOPPED 若为当前暂停子进程的返回状态，则为真，这种情况使用 WSTOPSIG 来获取使子进程暂停的信号编号。
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void simple_test()
{
	pid_t pid;
	char *message;
	int n;
	int exit_code;

	printf("fork program starting\n");
	pid = fork();

	switch(pid)
	{
	case -1:
		perror("fork failed");
		exit(1);

	case 0:
		message = "This is the child";
		n = 5;
		exit_code = 37;
		break;

	default:
		message = "This is the parent";
		n = 3;
		exit_code = 0;
		break;
	}

	for (; n > 0; --n) {
		puts(message);
		sleep(1);
	}

	if (pid != 0) {
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf("Child has finished: PID = %d\n", child_pid);
		if (WIFEXITED(stat_val))
			printf("Child exited with code: %d\n", WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");
	}

	exit(exit_code);
}

// 测试进程的退出状态
void pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d\n", WTERMSIG(status));
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

void test_pr_exit()
{
	pid_t pid;
	int status;

	// normal termination
	{
		if ((pid = fork()) < 0)
			perror("fork");
		else if (pid == 0)
			exit(7);		// child

		if (wait(&status) != pid)
			perror("wait");
		pr_exit(status);
	}
	
	// terminate by SIGABRT
	{
		if ((pid = fork()) < 0)
			perror("fork");
		else if (pid == 0)
			abort();		// child

		if (wait(&status) != pid)
			perror("wait");
		pr_exit(status);
	}
}

int main(int argc, char* argv[])
{
	//simple_test();
	test_pr_exit();

	return 0;
}
