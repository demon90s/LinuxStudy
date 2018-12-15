/*
	#include <curses.h>

	int getch(void);
	int getstr(char *string);
	int getnstr(char *string, int number_of_characters);
	int scanw(char *format, ...);

	读取键盘的输入。

	getch 读取字符并返回。
	getstr, getnstr 读取字符串。不会读取换行符。
	scanw 读取格式化的字符串。
 */

#include <curses.h>
#include <unistd.h>

void test_getch()
{
	int ch;

	ch = getch();

	printw("you enter: %c\n", ch);

	refresh();
	sleep(3);
}

void test_getstr()
{
	char str[12] = {0};

	getstr(str);
	//getnstr(str, 11);

	printw("\nyou enter: %s", str);

	refresh();
	sleep(3);
}

void test_scanw()
{
	char str[12];
	int num;

	printw("Enter str num: ");
	refresh();

	scanw("%s%d", str, &num);
	printw("you enter: %s %d\n", str, num);
	refresh();

	sleep(3);
}

int main()
{
	initscr();

	//test_getch();
	//test_getstr();
	test_scanw();

	endwin();

	return 0;
}
