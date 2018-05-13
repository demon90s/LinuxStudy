#include "Clock.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

namespace utility
{
void Test_Clock()
{
	Clock clock;
	std::cout << "timestamp: " << clock.Time() << std::endl;
	std::cout << "asc time: " << clock.AscTime() << std::endl;

	sleep(3);
	clock.Check();
	std::cout << "timestamp: " << clock.Time() << std::endl;
	std::cout << "asc time: " << clock.AscTime() << std::endl;
}

Clock::Clock() : m_time(0)
{
	memset(&m_local_time, 0, sizeof(m_local_time));
	memset(m_asc_time, 0, sizeof(m_asc_time));

	this->Check();
}

void Clock::Check()
{
	m_time = time(0);
	struct tm *p_tm = localtime(&m_time);
	m_local_time = *p_tm;
	strftime(m_asc_time, sizeof(m_asc_time), "%Y-%m-%d %H:%M:%S", p_tm);
}

}
