/*
 * 实验 logmask
 */

#include <syslog.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	openlog("logmask", LOG_PID|LOG_CONS, LOG_USER);
	syslog(LOG_INFO, "infomative message, pid = %d", getpid());
	syslog(LOG_DEBUG, "debug message, should appear");
	setlogmask(LOG_UPTO(LOG_NOTICE));
	syslog(LOG_DEBUG, "debug message, should not appear");

	return 0;
}
