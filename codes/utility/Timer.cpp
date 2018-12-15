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
		BooCallback(int id) : m_id(id) {}

		void OnTimer() override
		{
			std::cout << "BooCallback OnTimer, id: " << m_id << std::endl;
		}
	private:
		int m_id;
	};

	Timer timer;
	std::shared_ptr<ITimerCallback> callback1(new BooCallback(1));
	timer.CreateTimerItem(2000, callback1);

	std::shared_ptr<ITimerCallback> callback2(new BooCallback(2));
	timer.CreateTimerItem(1000, callback2);

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

	m_timer_item_list.sort();
}

}
