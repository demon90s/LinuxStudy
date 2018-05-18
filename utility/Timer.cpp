#include "Timer.h"
#include "HeartBeat.h"
#include <iostream>

namespace utility
{

void Test_Timer()
{
	class BooCallback : public ITimerCallback
	{
	public:
		void OnTimer() override
		{
			std::cout << "BooCallback OnTimer" << std::endl;
		}
	};

	Timer timer;
	std::shared_ptr<ITimerCallback> callback(new BooCallback);
	timer.CreateTimerItem(2000, callback);

	HeartBeat heart_beat(10); // 10ms 心跳检测一次
	heart_beat.Register(&timer, &Timer::Check);
	heart_beat.Run();
}

void Timer::Check()
{
	m_clock.Check();

	long long now = m_clock.MsTime();
	for (auto it = m_timer_item_list.begin(); it != m_timer_item_list.end(); )
	{
		if (now < it->trigger_ms_time)
		{
			break; // 定时器是按时间顺序插入的，前面的定时器触发不了，后面的也不会触发
		}

		it->callback->OnTimer();
		it = m_timer_item_list.erase(it);
	}
}

void Timer::CreateTimerItem(long long cd_ms, std::shared_ptr<ITimerCallback> callback)
{
	m_timer_item_list.push_back({m_clock.MsTime() + cd_ms, callback});
}

}
