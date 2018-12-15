/*
 * #include <fcntl.h>
 *
 * int fcntl(int filedes, int command, struct flock *flock_structure);
 *
 * 给 filedes 所指定的文件加/取消/查询一把锁，此锁的信息由 flock_structure 给出
 *
 * command 可以取值 F_GETLK F_SETLK F_SETLKW
 * flock_structure 的成员至少有：
 * - short l_type，锁类型，有 F_RDLCK (共享锁，读锁) F_WRLCK (独占锁，写锁) F_UNLCK (解锁)
 * - short l_whence 取值有 SEEK_SET SEEK_CUR SEEK_END
 * - off_t l_start 锁区域起点，l_whence 的偏移值
 * - off_t l_len 锁区域的字节数
 * - pid_t l_pid 持有锁的进程
 *
 * 函数成功返回非-1的值，失败返回-1 。
 *
 * 情况1：
 * 当 command 取值为 F_GETLK 时，函数用于获取文件的锁信息， flock_structure 代表想要给文件加的锁类型，其中
 * l_type 是想加的类型，l_whence l_start l_len 是锁定区域，将 l_pid 的初始值设置为-1 ，如果调用成功，
 * l_pid 被修改，说明不能加锁，l_pid 代表当前持有该锁的进程
 *
 * 情况2：
 * 当 command 取值为 F_SETLK 时，函数试图对文件加锁。 flock_structure 代表要加的锁类型，其中 l_type 是加锁
 * 的类型，l_whence l_start l_len 是锁定区域，l_pid 不使用。函数总是立即返回。
 * 如果 l_type 是解锁 F_UNLCK ，那么解锁的是自己加的锁。
 *
 * 情况3：
 * 当 command 取值为 F_SETLKW 时，作用和 F_SETLK 相同，但当无法获取锁的时候，函数调用将等待直到可以操作为止
 *
 * 当文件描述符被关闭，其上的锁都会被清除。程序结束也会清除各种锁。
 *
 * 注意：使用该方法给文件上的都是建议锁，不能阻止其他程序使用 read 或 write 来操作文件。
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char* const usage="Usage: ./fcntl_flock <getrdlck|getwrlck|setrdlck|setwrlck|unlock|setlkw>";
const char* const file="/tmp/test_fcntl_flock.tmp";
int fd;

// 询问文件上的读锁
void test_GETLK_RDLCK()
{
	struct flock region;
	region.l_type = F_RDLCK;
	region.l_whence = SEEK_SET;
	region.l_start = 0;
	region.l_len = 10;
	region.l_pid = -1;

	if (fcntl(fd, F_GETLK, &region) == -1) {
		perror("fcntl");
		return;
	}

	if (region.l_pid != -1) {
		printf("Get RDLCK(%lu,%lu) failed, pid %d own lock\n", region.l_start, region.l_start + region.l_len, region.l_pid);
	}
	else {
		printf("Get RDLCK(%lu,%lu) succ, you can set RDLCK to this file\n", region.l_start, region.l_start + region.l_len);
	}
}

// 询问文件上的写锁
void test_GETLK_WRLCK()
{
	struct flock region;
	region.l_type = F_WRLCK;
	region.l_whence = SEEK_SET;
	region.l_start = 0;
	region.l_len = 10;
	region.l_pid = -1;

	if (fcntl(fd, F_GETLK, &region) == -1) {
		perror("fcntl");
		return;
	}

	if (region.l_pid != -1) {
		printf("Get WRLCK(%lu,%lu) failed, pid %d own lock\n", region.l_start, region.l_start + region.l_len, region.l_pid);
	}
	else {
		printf("Get WRLCK(%lu,%lu) succ, you can set WRLCK to this file\n", region.l_start, region.l_start + region.l_len);
	}
}

// 给文件上一把读锁
void test_SETLK_RDLCK()
{
	struct flock region;
	region.l_type = F_RDLCK;
	region.l_whence = SEEK_SET;
	region.l_start = 0;
	region.l_len = 10;
	region.l_pid = -1;

	if (fcntl(fd, F_SETLK, &region) == -1) {
		perror("fcntl");
		return;
	}

	printf("Set RDLCK(%lu,%lu) succ\n", region.l_start, region.l_start + region.l_len);
	sleep(60);
}

// 给文件上一把写锁
void test_SETLK_WRLCK()
{
	struct flock region;
	region.l_type = F_WRLCK;
	region.l_whence = SEEK_SET;
	region.l_start = 0;
	region.l_len = 10;
	region.l_pid = -1;

	if (fcntl(fd, F_SETLK, &region) == -1) {
		perror("fcntl");
		return;
	}

	printf("Set WRLCK(%lu,%lu) succ\n", region.l_start, region.l_start + region.l_len);
	sleep(60);
}

// 给文件解锁，先上一个独占锁，然后过上30秒解锁
void test_SETLK_UNLCK()
{
	struct flock region;
	region.l_whence = SEEK_SET;
	region.l_start = 0;
	region.l_len = 10;
	region.l_pid = -1;

	region.l_type = F_WRLCK;
	if (fcntl(fd, F_SETLK, &region) == -1) {
		perror("fcntl");
		return;
	}
	printf("Set WRLCK(%lu,%lu) succ, wait 30 second, I will unlock it.\n", region.l_start, region.l_start + region.l_len);

	sleep(30);

	region.l_type = F_UNLCK;
	if (fcntl(fd, F_SETLK, &region) == -1) {
		perror("fcntl");
		return;
	}

	printf("unlock WRLCK(%lu,%lu) succ\n", region.l_start, region.l_start + region.l_len);
	sleep(60);
}

// 等待着获取独占锁
void test_SETLKW()
{
	struct flock region;
	region.l_whence = SEEK_SET;
	region.l_start = 0;
	region.l_len = 10;
	region.l_pid = -1;

	printf("Now I want to Set WRLCK(%lu,%lu)\n", region.l_start, region.l_start + region.l_len);

	region.l_type = F_WRLCK;
	if (fcntl(fd, F_SETLKW, &region) == -1) {
		perror("fcntl");
		return;
	}

	printf("Set WRLCK(%lu,%lu) succ\n", region.l_start, region.l_start + region.l_len);
}

int main(int argc, char* argv[])
{
	char buffer[20] = {0};
	const char* cmd;

	if (argc != 2) {
		printf("%s\n", usage); 
		exit(EXIT_FAILURE);
	}

	// 先打开测试文件，之后在其上测试各种锁操作
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	// 给文件写一个长度
	write(fd, buffer, sizeof(buffer));

	// 根据命令行参数决定测试模块
	cmd = argv[1];
	if (strcmp(cmd, "getrdlck") == 0) {
		test_GETLK_RDLCK();
	}
	else if (strcmp(cmd, "getwrlck") == 0) {
		test_GETLK_WRLCK();
	}
	else if (strcmp(cmd, "setrdlck") == 0) {
		test_SETLK_RDLCK();
	}
	else if (strcmp(cmd, "setwrlck") == 0) {
		test_SETLK_WRLCK();
	}
	else if (strcmp(cmd, "unlock") == 0) {
		test_SETLK_UNLCK();
	}
	else if (strcmp(cmd, "setlkw") == 0) {
		test_SETLKW();
	}
	else {
		printf("%s\n", usage); 
		close(fd);
		exit(EXIT_FAILURE);
	}

	close(fd);

	exit(EXIT_SUCCESS);
}
