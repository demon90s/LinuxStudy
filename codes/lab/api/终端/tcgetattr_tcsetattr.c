/*
 * #include <termios.h>
 *
 * int tcgetattr(int fd, struct termios *termios_p);
 * int tcsetattr(int fd, int actions, const struct termios *termios_p);
 *
 * 获取/设置与 fd 关联的终端属性为 termios_p ，从而控制终端的行为。
 *
 * actions 表示修改方式：
 * - TCSANOW：立即对值进行修改
 * - TCSADRAIN：等当前的输出完成后再对值进行修改
 * - TCSAFLUSH：等当前的输出完成后再对值进行修改，但丢弃还未从 read 调用返回的当前可用的任何输入
 *
 * termios 结构至少包含了这些成员：
 *
 * struct termios {
 * 		tcflag_t c_iflag;			// 输入模式
 * 		tcflag_t c_oflag;			// 输出模式
 * 		tcflag_t c_cflag;			// 控制模式
 * 		tcflag_t c_lflag;			// 本地模式
 * 		cc_t	 c_cc[NCCS];		// 特殊控制字符
 * };
 *
 * 具体取值查阅资料。
 *
 * 函数成功返回0 。
 */

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

// 设置不回显显示
void set_noecho()
{
	struct termios attr;
	tcgetattr(1, &attr);
	attr.c_lflag &= ~ECHO;
	tcsetattr(1, TCSAFLUSH, &attr);

	printf("Enter some word: ");
	char buffer[1024];
	fgets(buffer, sizeof(buffer), stdin);
	printf("\nYour input: %s", buffer);
}

// 设置非标准模式（可以变成输入字符后立刻给程序处理，而不必等待回车）
void set_icanon()
{
	struct termios attr;
	tcgetattr(1, &attr);
	attr.c_lflag &= ~ICANON;
	attr.c_cc[VTIME] = 0;
	attr.c_cc[VMIN] = 1; // VMIN = 1, VTIME = 0 表示当输入了一个字符后，底层 read 就返回
	tcsetattr(1, TCSAFLUSH, &attr);

	while (1) {
		printf("Enter character(q to quit): ");
		int c;
		c = fgetc(stdin);
		printf("\nYour input: %c\n", c);

		if (c == 'q') break;
	}
}

// 设置忽略掉终端信号，比如 CTRL + C
void set_ignore_sig()
{
	struct termios attr;
	tcgetattr(1, &attr);
	attr.c_lflag &= ~ISIG;
	tcsetattr(1, TCSAFLUSH, &attr);

	while (1) {
		printf("CTRL + C not work~~~\n");
		sleep(1);
	}
}

int main()
{
	struct termios initattr;
	tcgetattr(1, &initattr);

	//set_noecho();
	//set_icanon();
	set_ignore_sig();

	tcsetattr(1, TCSAFLUSH, &initattr);

	return 0;
}
