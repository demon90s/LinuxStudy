// 实验：用C语言编写的菜单例程（完整的终端控制）

// 使用 terminfo

#include <unistd.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

static FILE *output_stream = (FILE*)0;

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);
int char_to_terminal(int char_to_write);
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

		sleep(1);

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
	int screenrow, screencol = 10;
	char **option;
	char *cursor, *clear;

	output_stream = out;

	setupterm(NULL, fileno(out), (int*)0);
	cursor = tigetstr("cup");
	clear = tigetstr("clear");

	screenrow = 4;
	tputs(clear, 1, char_to_terminal);
	tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
	
	fprintf(out, "Choice: %s", greet);
	screenrow += 2;
	option = choices;

	while (*option) {
		tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
		fprintf(out, "%s", *option);
		screenrow++;
		option++;
	}
	fprintf(out, "\n");

	do {
		fflush(out);
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
			tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
			fprintf(out, "Incorrect choice, select again\n");
		}
	} while (!chosen);

	tputs(clear, 1, char_to_terminal);
	return selected;
}

int char_to_terminal(int char_to_write)
{
	if (output_stream) fputc(char_to_write, output_stream);
	return 0;
}
