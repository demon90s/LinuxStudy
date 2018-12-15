#include "HeartBeat.h"
#include <unistd.h>
#include <iostream>

namespace utility
{

void Test_HeartBeat()
{
	class Foo
	{
	public:
		Foo(HeartBeat *heart_beat) : m_heart_beat(heart_beat) {}
	
		void Update()
		{
			std::cout << "Hello, I am Foo, HeartBeat interval ms: " << m_heart_beat->LastIntervalMs() << std::endl;
		}

	private:
		HeartBeat *m_heart_beat;
	};

	HeartBeat heart_beat(500);
	Foo foo(&heart_beat);
	if (heart_beat.Register(&foo, &Foo::Update))
	{
		heart_beat.Run();
	}
	else
	{
		std::cerr << "Register fail" << std::endl;
	}
}

HeartBeat::HeartBeat(long long update_interval_ms) : m_update_interval_ms(update_interval_ms), m_last_update_ms_time(0), m_last_interval_ms(0)
{
}

void HeartBeat::Run()
{
	while (true)
	{
		m_clock.Check();

		if (m_last_update_ms_time == 0) m_last_interval_ms = 0;
		else m_last_interval_ms = m_clock.MsTime() - m_last_update_ms_time;
		m_last_update_ms_time = m_clock.MsTime();

		for (auto it = m_item_cache.begin(); it != m_item_cache.end(); )
		{
			auto &obj = it->second;
			if (obj->IsDelete())
			{
				m_item_cache.erase(it++);
			}
			else
			{
				obj->Update();
				++it;
			}
		}

		usleep(1000 * m_update_interval_ms);
	}
}

void HeartBeat::UnRegister(void *obj)
{
	auto it = m_item_cache.find(obj);
	if (it == m_item_cache.end())
	{
		return;
	}

	it->second->SetDelete();
}

}
