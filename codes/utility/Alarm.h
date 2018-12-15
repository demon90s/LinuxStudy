#ifndef ALARM_H
#define ALARM_H

namespace utility
{

/*
 * 封装alarm函数，设定一个事件绑定到SIGALRM信号，并在若干秒后可检测触发
 *
 * 流程：Register -> Check -> Deal
 */
class Alarm
{
public:
	enum Event
	{
		EventIdle = 0,
		EventTest = 1,
	};

	Alarm() = default;

	// 注册一个alarm事件，并在若干秒后才能触发
	bool Register(Event event, int sec = 0);

	// 检测是否到了触发时间，如果到了，则发送alarm信号给本进程
	bool Check();

	// 处理事件
	void Deal();
private:
	static void SigCallback(int sig);
};

extern void Test_Alarm();

}
#endif // ALARM_H
