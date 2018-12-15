/*
	#include <curses.h>

	WINDOW *newpad(int number_of_lines, int number_of_columns);
	int prefresh(WINDOW *pad_ptr, int pad_row, int pad_colomn,
				int screen_row_min, int screen_col_min,
				int screen_row_max, int screen_col_max);

	newpad 创建一个 pad ，有别于 window ，它可以位于屏幕的外面，但对它的读写操作接口和 window 都一样。
	pad 通常用于一个逻辑屏幕，在需要的时候将内容刷新到正式屏幕。

	prefresh 将 pad 的从 pad_row,pad_colomn 开始的内容刷新到显示区域，这个区域是：{(screen_row_min, screen_col_min), (screen_row_max, screen_col_max)}
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	WINDOW *pad;
	int x, y;

	initscr();

	pad = newpad(10, 10);
	for (y = 0; y < 10; y++)
		for (x = 0; x < 10; x++) {

		if (y >= 5)
			mvwprintw(pad, y, x, "X");
		else
			mvwprintw(pad, y, x, "O");
	}
	refresh();
	sleep(1);

	prefresh(pad, 0, 0, 0, 0, 4, 9);
	sleep(1);
	prefresh(pad, 5, 0, 10, 10, 14, 19);
	sleep(1);
	prefresh(pad, 0, 0, 20, 20, 29, 29);

	pause();
	endwin();

	return 0;
}
