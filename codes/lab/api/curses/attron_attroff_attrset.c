/*
	#include <curses.h>

	int attron(chtype attribute);
	int attroff(chtype attribute);
	int attrset(chtype attribute);

	开启、关闭、设置字符在屏幕上的显示方式为 attribute 。其去值可以有：

	- A_BLINK
	- A_BOLD
	- A_DIM
	- A_REVERSE
	- A_STANDOUT
	- A_UNDERLINE

	attron attroff 不会影响其他设定，而 attrset会（覆盖） 。
 */

#include <curses.h>
#include <unistd.h>

void test_attron_attroff()
{
	printw("Normal text\n");

	attron(A_BOLD);
	printw("Bold text\n");
	attroff(A_BOLD);

	attron(A_UNDERLINE);
	printw("Underline text\n");
	attroff(A_UNDERLINE);

	refresh();
}

void test_attrset()
{
	printw("Normal text\n");

	attrset(A_BOLD);
	printw("Bold text\n");

	attrset(A_UNDERLINE);
	printw("Underline text\n");

	refresh();
}

int main()
{
	initscr();

	test_attron_attroff();
	
	//test_attrset();

	sleep(2);
	endwin();

	return 0;
}
