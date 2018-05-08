#ifndef PROCESS_START
#define PROCESS_START

#include <sys/types.h>
#include <set>

namespace utility
{

/*
 * 使用fork生成子进程，并需要注册子进程退出时的回调函数
 */
class ProcessFork
{
public:
	typedef void (*Callback)(pid_t child_pid, int ret);
	ProcessFork(Callback call_back_func) : m_call_back_func(call_back_func), m_child_count(0) {}

	pid_t Fork();	// fork一个子进程，返回fork的返回值
	size_t Wait(); 	// 非阻塞检查所有子进程退出情况，如果子进程退出，调用回调函数，返回当前子进程个数

private:
	Callback m_call_back_func;
	size_t m_child_count;
};

extern void Test_ProcessFork();

}

#endif
