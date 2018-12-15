/*
	#include <curses.h>

	WINDOW* newwin(int num_of_lines, int num_of_cols, int start_y, int start x);
	int delwin(WINDOW *window_to_delete);

	newwin 创建一个新的 num_of_lines * num_of_cols 的窗口，其左上角位于屏幕的 start_y, start_x 处。创建失败返回 NULL 。
	新窗口和其他窗口之间是独立的。
	新创建的窗口会覆盖掉已有的窗口的内容。

	delwin 删除一个窗口。
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	WINDOW *new_window;

	initscr();

	new_window = newwin(10, 10, 0, 0);
	if (new_window) {
		box(new_window, '|', '-');
	}
	wrefresh(new_window);

	sleep(3);

	delwin(new_window);
	refresh();

	while (1) { sleep(1); }

	endwin();
	return 0;
}
