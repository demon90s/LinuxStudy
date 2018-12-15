/*
 * #include <sys/types.h>
 * #include <unistd.h>
 * uid_t getuid(void);
 * char *getlogin(void);
 *
 * getuid 返回程序关联的UID，通常是启动程序的用户的UID， uid_t 是一个小整数。
 *
 * getlogin 返回用户的名字。
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	uid_t uid;
	char* user_name;

	uid = getuid();
	user_name = getlogin();

	printf("uid: %d\n", uid);
	printf("user_name: %s\n", user_name);

	return 0;
}
