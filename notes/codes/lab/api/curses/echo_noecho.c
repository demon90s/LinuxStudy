/*
	#include <curses.h>

	int echo(void);
	int noecho(void);

	设置键盘读取的模式为回显/不回显。
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	char passwd[128];

	initscr();

	noecho();
	printw("Enter password: ");
	getstr(passwd);
	echo();
	printw("you enter: %s", passwd);

	refresh();
	sleep(3);

	endwin();

	return 0;
}
