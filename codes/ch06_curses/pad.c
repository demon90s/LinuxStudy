// 实验：使用pad

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
	WINDOW *pad_ptr;
	int x, y;
	int pad_lines;
	int pad_cols;
	char disp_char;

	initscr();

	pad_lines = LINES + 50;
	pad_cols = COLS + 50;
	pad_ptr = newpad(pad_lines, pad_cols);
	disp_char = 'a';

	for (x = 0; x < pad_lines; x++) {
		for (y = 0; y < pad_cols; y++) {
			mvwaddch(pad_ptr, x, y, disp_char);
			if (disp_char == 'z') disp_char = 'a';
			else disp_char++;
		}
	}

	refresh();
	sleep(2);

	// 将 pad 的不同区域绘制到屏幕的不同位置上
	prefresh(pad_ptr, 5, 7, 2, 2, 9, 9);
	sleep(1);
	prefresh(pad_ptr, LINES + 5,  COLS + 7, 5, 5, 21, 19);
	sleep(1);
	delwin(pad_ptr);

	endwin();

	return 0;
}
