/*
 * #include <syslog.h>
 *
 * void closelog();
 * void openlog(const char *ident, int logopt, int facility);
 * int setlogmask(int maskpri);
 *
 * openlog 用来改变 syslog 函数的表达方式。它设置一个字符串 ident 将它放置在每条日志
 * 的前面（如果为 NULL ，则把程序的名字放到前面）。
 *
 * facility 设置的是 syslog 调用的默认设施值，参考一下 syslog.c 程序。
 *
 * logopt 表示对 syslog 行为的配置。可以是：
 *
 * LOG_PID				在日志信息中包含进程描述符
 * LOG_CONS				如果信息不能被记录到日志文件中，就把它们发送到控制台
 * LOG_ODELAY			在第一次调用 syslog 时才打开日志设施
 * LOG_NDELAY			立即打开日志设施，而不是等到第一次记录日志时
 *
 * 它们的按位或。
 *
 * openlog 函数会分配并打开一个文件描述符，并通过它来写日志，然后可以通过调用 closelog 函数关闭它。
 *
 * setlogmask 用于设置一个日志掩码，未置位的 priority 将被丢弃。
 * LOG_MASK(priority) 创建一个只包含 priority 的掩码。
 * LOG_UPTO(priority) 创建一个 >= priority 的掩码 。
 *
 * setlogmask 把设定之前的掩码返回。
 */

#include <syslog.h>

// 在 CentOS 7上面，观察 /var/log/message

int main()
{
	int old_mask;

	openlog("openlog_setlogmask", LOG_PID, LOG_USER);
	old_mask = setlogmask(LOG_UPTO(LOG_ERR));
	syslog(LOG_ERR, "error message occur");
	syslog(LOG_WARNING, "warning message may not occur");

	setlogmask(old_mask);
	syslog(LOG_WARNING, "warning message now occur");

	closelog();

	return 0;
}
