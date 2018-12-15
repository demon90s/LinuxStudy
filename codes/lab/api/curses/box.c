/*
	#include <curses.h>

	int box(WINDOW *win_ptr, chtype vertical_char, chtype horizontal_char);

	围绕 win_ptr 代表的窗口绘制一个 box 。

	可自选 vertival_char 和 horizontal_char 。
	也可以使用默认值0 。
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	initscr();

	box(stdscr, 0, 0);
	refresh();

	getch();

	endwin();

	return 0;
}
