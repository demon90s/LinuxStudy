/*
	#include <curses.h>

	WINDOW* subwin(WINDOW *parent, int num_of_lines, int num_of_cols, int start_y, int start_x);
	int delwin(WINDOW* window_to_delete);

	创建 parent 的子窗口，大小是 num_of_lines * num_of_cols ，位于父窗口的 start_y, startx 
	功能和新的窗口是一样的，只不过与父窗口共享了字符存储，因此会修改父窗口的内容，在调用了
	delwin 删除子窗口后，其修改就会保留下来

	在刷新屏幕之前，必须先对父窗口调用 touchwin
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	WINDOW *sub_window;

	initscr();

	sub_window = subwin(stdscr, 10, 10, 0, 0);
	//sub_window = newwin(10, 10, 0, 0);
	box(sub_window, '|', '-');

	touchwin(stdscr);
	wrefresh(sub_window);

	sleep(2);

	delwin(sub_window);

	mvprintw(11, 0, "sub window deleted\n");
	refresh();
	sleep(2);

	endwin();

	return 0;
}
