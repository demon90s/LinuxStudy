#ifndef TIMER_H
#define TIMER_H

#include <list>
#include <memory>
#include "Clock.h"

namespace utility
{

extern void Test_Timer();

/*
 * 定时器
 */
class ITimerCallback
{
public:
	virtual ~ITimerCallback() {}
	virtual void OnTimer() = 0;
};

class Timer
{
	using Callback = std::shared_ptr<ITimerCallback>;

public:
	Timer() = default;

	void Check();

	// 创建毫秒级定时器，cd_ms毫秒后，触发callback_obj->OnTimer(), 之后callback_obj->Free()
	void CreateTimerItem(long long cd_ms, Callback callback);

private:
	Clock m_clock;

	struct TimerItem
	{
		TimerItem(long long _trigger_ms_time, Callback _callback) : trigger_ms_time(_trigger_ms_time), callback(_callback) {}
		bool operator<(const TimerItem &rhs) const
		{
			return trigger_ms_time < rhs.trigger_ms_time;
		}

		long long trigger_ms_time;
		Callback callback;
	};
	std::list<TimerItem> m_timer_item_list;
};
}

#endif
