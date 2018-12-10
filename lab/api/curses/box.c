/*
	#include <curses.h>

	int box(WINDOW *win_ptr, chtype vertical_char, chtype horizontal char);

	围绕 win_ptr 代表的窗口绘制一个 box 。
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	initscr();

	box(stdscr, '|', '-');
	refresh();

	while (1) { sleep(1); }

	endwin();

	return 0;
}
