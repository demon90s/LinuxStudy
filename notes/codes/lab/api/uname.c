/*
 * #include <sys/utsname.h>
 *
 * int uname(struct utsname *name);
 *
 * 把主机信息写入 name 。
 *
 * utsname 结构包含下面的成员：
 *
 * char sysname[]			操作系统名
 * char nodename[]			主机名
 * char release[]			系统发行级别
 * char version[]			系统版本号
 * char machine[]			硬件类型
 *
 * 调用成功返回一个非负整数，否则返回-1并设置 errno 。
 */

#include <sys/utsname.h>
#include <stdio.h>

int main()
{
	struct utsname name;
	if (uname(&name) >= 0) {
		printf("sysname: %s\n", name.sysname);
		printf("nodename: %s\n", name.nodename);
		printf("release: %s\n", name.release);
		printf("version: %s\n", name.version);
		printf("machine: %s\n", name.machine);
	}

	return 0;
}
