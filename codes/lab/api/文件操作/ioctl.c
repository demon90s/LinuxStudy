/*
	#include <sys/ioctl.h>

	int ioctl(int filedes, int cmd, ...);

	ioctl 对描述副 filedes 引用的对象执行 cmd 参数给出的操作。
	根据特定设备所支持的操作的不同，它还可能会有一个可选的第三参数。
 */

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <stdio.h>

int main()
{
	int tty_fd;

	tty_fd = open("/dev/tty", O_RDWR);
	if (tty_fd == -1) {
		perror("open");
		return 1;
	}

	// 打开键盘上的 LED 灯
	ioctl(tty_fd, KDSETLED, LED_NUM|LED_CAP|LED_SCR);

	close(tty_fd);

	getchar();

	return 0;
}
