#ifndef HEATR_BEAT_H
#define HEATR_BEAT_H

#include <map>
#include <memory>
#include "Clock.h"

namespace utility
{
extern void Test_HeartBeat();

/*
 * 心跳器，可以将任何对象的方法注册进来，每次循环中执行一次
 */

class IHeartBeatItem
{
public:
	virtual ~IHeartBeatItem() {}
	virtual void Update() = 0;

	bool IsDelete() const { return m_is_delete; }
	void SetDelete() { m_is_delete = true; }

private:
	bool m_is_delete = false;
};

template<typename T>
class HeartBeatItem : public IHeartBeatItem
{
	typedef void (T::*HeartBeatFunc)();
public:
	HeartBeatItem(T *obj, HeartBeatFunc func) : m_obj(obj), m_func(func) {}

	void Update() override
	{
		(m_obj->*m_func)();
	}

private:
	T *m_obj; // 不负责管理此Obj的生命周期
	HeartBeatFunc m_func;
};

class HeartBeat
{
public:
	HeartBeat(long long update_interval_ms = 1000);
	HeartBeat(const HeartBeat&) = delete;
	HeartBeat& operator=(const HeartBeat&) = delete;

	void Run();

	template<typename T> bool Register(T *obj, void (T::*func)());
	void UnRegister(void *obj);

	long long LastIntervalMs() const { return m_last_interval_ms; }

private:
	Clock m_clock;

	long long m_update_interval_ms;		// 心跳间隔

	long long m_last_update_ms_time;	// 上一次心跳毫秒时间戳
	long long m_last_interval_ms;		// 上一次心跳间隔

	std::map<void*, std::shared_ptr<IHeartBeatItem>> m_item_cache; // addr -> obj_ptr
};

template<typename T> inline
bool HeartBeat::Register(T *obj, void (T::*func)())
{
	if (m_item_cache.find(obj) != m_item_cache.end())
	{
		return false;
	}

	auto item = &m_item_cache[obj];
	std::shared_ptr<IHeartBeatItem> tmp_ptr(new HeartBeatItem<T>(obj, func));
	*item = tmp_ptr;

	return true;
}

}

#endif
