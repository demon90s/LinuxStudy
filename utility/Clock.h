#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

namespace utility
{
extern void Test_Clock();

class Clock
{
public:
	Clock();

	// 刷新当前时间
	void Check();

	time_t Time() const { return m_time; }
	const char *AscTime() const { return m_asc_time; }

private:
	time_t m_time;
	struct tm m_local_time;
	char m_asc_time[64];
};

}

#endif // CLOCK_H
