#include "ProcessFork.h"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>
#include <string>

namespace utility
{

void Test_ProcessFork()
{
	auto call_back_func = [](pid_t child_pid, int ret)
	{
		printf("Child[%d] ret: %d\n", child_pid, ret);
	};
	ProcessFork proc_fork(call_back_func);

	// 开几个子进程测试
	srand(time(0));
	for (int i = 0; i < 5; ++i)
	{
		int t = rand() % 5 + 1;
		auto pid = proc_fork.Fork();
		if (pid == 0)
		{
			printf("I am child process, I am doing some job for %d seconds\n", t);
			sleep(t);
			exit(t);
		}
	}
	
	// 父进程开启等待
	while (proc_fork.Wait() > 0)
	{
		//printf("Waiting for child(ren) return\n");
		sleep(1);
	}
}

pid_t ProcessFork::Fork()
{
	pid_t pid;
	
	pid = fork();
	switch(pid)
	{
	case -1:
		perror("fork failed");
		break;

	case 0:
		break;

	default:
		printf("Fork child %d\n", pid);
		++m_child_count;
		break;
	}

	return pid;
}

size_t ProcessFork::Wait()
{
	if (m_child_count == 0)
		return 0;

	auto loop_count = m_child_count;
	while (loop_count-- > 0)
	{
		int stat_loc;
		auto pid = waitpid(-1, &stat_loc, WNOHANG);
		if (pid == -1)
		{
			std::string error = "waitpid " + std::to_string(pid) + " failed";
			perror(error.c_str());
		}
		else if (pid > 0)
		{
			auto ret = WEXITSTATUS(stat_loc);
			m_call_back_func(pid, ret);

			--m_child_count;
		}
	}

	return m_child_count;
}

}
