#include "Alarm.h"

#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <signal.h>

namespace utility
{

static Alarm::Event event_lock = Alarm::EventIdle;
static Alarm::Event deal_event = Alarm::EventIdle;
static time_t alarm_timestamp = 0;

bool Alarm::Register(Event event, int sec)
{
	if (event == EventIdle || event_lock)
		return false;

	event_lock = event;
	alarm_timestamp = time(0) + sec;
	signal(SIGALRM, SigCallback);

	return true;
}

bool Alarm::Check()
{
	auto now = time(0);
	if (alarm_timestamp == 0 || now < alarm_timestamp)
		return false;

	kill(getpid(), SIGALRM);
	return true;
}

void Alarm::SigCallback(int sig)
{
	deal_event = event_lock;
}

void Alarm::Deal()
{
	if (!deal_event)
		return;

	Event event = deal_event;
	deal_event = event_lock = EventIdle;
	alarm_timestamp = 0;

	switch(event)
	{
	case EventIdle:
	{
	}
	break;

	case EventTest:
	{
		printf("[DEBUG] Alarm::Deal EventTest\n");
	}
	break;
	}
}

void Test_Alarm()
{
	Alarm alarm_tool;
	auto ret = alarm_tool.Register(Alarm::EventTest, 3);

	if (!ret)
	{
		fprintf(stderr, "Register event failed\n");
		return;
	}

	while (!alarm_tool.Check())
	{
		printf("waiting ...\n");
		sleep(1);
	}

	alarm_tool.Deal();
}
}
