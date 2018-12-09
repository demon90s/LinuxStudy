/*
	#include <curses.h>

	int delch(void);
	int deleteln(void);

	delch 删除掉光标处的字符，然后把后面的内容往前移动一个字符。
	deleteln 删除掉当前行，后面的行往前移动一行。
*/

#include <curses.h>

void test_delch()
{
	printw("Hello World");

	move(0, 0);

	delch();

	refresh();
}

void test_deleteln()
{
	move(2, 0);
	printw("Hello World\nWow Nice try\nHyHy BUG~~~");

	move(3, 0);
	deleteln();

	refresh();
}

int main()
{
	initscr();

	test_delch();
	test_deleteln();

	endwin();

	return 0;
}
