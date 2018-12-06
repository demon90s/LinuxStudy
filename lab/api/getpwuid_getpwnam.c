/*
 * #include <sys/types.h>
 * #include <pwd.h>
 *
 * struct passwd *getpwuid(uid_t uid);
 * struct passwd *getpwnam(const char *name);
 *
 * 获取用户信息，分别通过 uid 和 登陆名。
 *
 * 结构 passwd 有这些成员：
 *
 * char *pw_name		用户登陆名
 * uid_t pw_uid			UID
 * git_t pw_gid			GID
 * char *pw_dir			用户家目录
 * char *pw_gecos		用户全名
 * char *pw_shell		用户默认 shell
 *
 * 出错返回空指针，并置 errno 。
 */

#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main()
{
	struct passwd *pw;

	pw = getpwuid(0); // 0 就是 root
	if (pw) {
		printf("name: %s, uid: %d, gid: %d, home: %s, gecos: %s, shell: %s\n",
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_gecos, pw->pw_shell);
	}

	pw = getpwnam("sshd");
	if (pw) {
		printf("name: %s, uid: %d, gid: %d, home: %s, gecos: %s, shell: %s\n",
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_gecos, pw->pw_shell);
	}

	return 0;
}
