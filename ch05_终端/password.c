// 实验：使用termios结构的密码程序

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 8

int main()
{
	struct termios initialrsettings, newrsettings;
	char password[PASSWORD_LEN + 1];

	// 获取当前设置，以便还原
	tcgetattr(fileno(stdin), &initialrsettings);

	// 关闭 ECHO 标志，使得输入不回显
	newrsettings = initialrsettings;
	newrsettings.c_lflag &= ~ECHO;

	printf("Enter password: ");

	// 设置终端属性，然后读取密码，之后还原终端属性
	if (tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0) {
		fprintf(stderr, "Could not set attributes\n");
	}
	else {
		fgets(password, PASSWORD_LEN, stdin);
		tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
		fprintf(stdout, "\n You entered %s\n", password);
	}

	exit(0);
}
