/*
 * #include <syslog.h>
 * void syslog(int priority, const char* message, ...);
 *
 * 向系统的日志设施发送一条日志信息。
 * 这条信息包含消息头和消息体 message ，消息头根据设施值和当前的时间创建。
 * message 是格式串，转换控制符 %m 可以用于插入与 errno 对应的出错消息。
 * 其余的转换说明类似 printf 。
 *
 * 日志设施可能是某一个文件，或者广播到终端。
 *
 * 比如 /var/log/message
 *
 * priority 是一个设施值和一个严重级别的按位或，严重级别的取值有：
 * 
 * LOG_EMERG			情急情况
 * LOG_ALERT			高优先级故障，例如数据库崩溃
 * LOG_CRIT				严重错误，例如硬件故障
 * LOG_ERR				错误
 * LOG_WARNING			警告
 * LOG_NOTICE			需要注意的特殊情况
 * LOG_INFO				一般信息
 * LOG_DEBUG			调试信息
 *
 * 设施值默认为 LOG_USER ，还可以取值 LOG_LOCAL0 LOG_LOCAL1 ... LOG_LOCAL7,
 * 其含义由本地管理员指定。
 *
 */

#include <syslog.h>
#include <stdio.h>

int main()
{
	FILE *f;
	f = fopen("not_here", "r");
	if (!f)
		syslog(LOG_ERR | LOG_USER, "oops - %m\n");

	syslog(LOG_EMERG, "This is a emergency\n");

	return 0;
}
