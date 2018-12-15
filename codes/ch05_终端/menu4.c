// 实验：用C语言编写的菜单例程（读取每个字符）

// 修改 termios ，使得可以不需要输入回车而读取字符。

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);
void checktty();

int main()
{
	checktty();

	int choice = 0;
	FILE *in, *out;
	struct termios initial_settings, new_settings;

	in = fopen("/dev/tty", "r");
	out = fopen("/dev/tty", "w");
	if (!in || !out) {
		fprintf(stderr, "Unable to open /dev/tty\n");
		return 1;
	}

	// 获取原始终端属性，设置终端属性，控制输出行为
	tcgetattr(fileno(in), &initial_settings);
	tcgetattr(fileno(in), &new_settings);
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_lflag &= ~ISIG;
	if (tcsetattr(fileno(in), TCSANOW, &new_settings) != 0) {
		fprintf(stderr, "could not set attributes\n");
	}

	do {
		choice = getchoice("Please select an action", menu, in, out);
		printf("You have chosen: %c\n", choice);

	} while (choice != 'q');

	if (0 != tcsetattr(fileno(in), TCSANOW, &initial_settings)) {
		fprintf(stderr, "[ERROR] tcsetattr failed\n");
		return 1;
	}

	fclose(in);
	fclose(out);

	return 0;
}

// 检查标准输出是否连接了终端，如果没有，则给予一条警告
void checktty()
{
	if (!isatty(fileno(stdout))) {
		fprintf(stderr, "[WARNING] You are not a terminal!\n");
	}
}

// 程序核心代码，负责显示菜单及读取用户输入
int getchoice(char *greet, char *choices[], FILE *in, FILE *out)
{
	int chosen = 0;
	int selected;
	char **option;

	do {
		fprintf(out, "Choice: %s\n", greet);
		option = choices;
		while (*option) {
			fprintf(out, "%s\n", *option);
			option++;
		}

		selected = fgetc(in);

		option = choices;
		while (*option) {
			if (selected == *option[0]) {
				chosen = 1;
				break;
			}
			option++;
		}
		if (!chosen) {
			fprintf(out, "Incorrect choice, select again!\n");
		}

	} while (!chosen);

	return selected;
}
