// 实验：用C语言编写的菜单例程（使用/dev/tty）

// 如果使用这样的命令启动程序，即使被重定向，仍然会把 menu 正常输出到终端：
//
// $ ./menu3 > log
//
// 其余的，重定向到 log

#include <unistd.h>
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

	in = fopen("/dev/tty", "r");
	out = fopen("/dev/tty", "w");
	if (!in || !out) {
		fprintf(stderr, "Unable to open /dev/tty\n");
		return 1;
	}

	do {
		choice = getchoice("Please select an action", menu, in, out);
		printf("You have chosen: %c\n", choice);

	} while (choice != 'q');

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
		while (fgetc(in) != '\n');

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
