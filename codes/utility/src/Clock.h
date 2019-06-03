#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

namespace utility
{
extern void Test_Clock();

/*
 * 提供获取时间相关方法
 */
class Clock
{
public:
	Clock();

	// 刷新当前时间
	void Check();

	time_t Time() const { return m_time; }
	long long MsTime() const { return m_ms_time; }
	const char *AscTime() const { return m_asc_time; }

private:
	time_t m_time;						// 时间戳
	long long m_ms_time;				// 毫秒时间戳
	struct tm m_local_time;
	char m_asc_time[64];				// 时间字符串，e.g. 2018-05-18 09:20:59
};

}

#endif // CLOCK_H
