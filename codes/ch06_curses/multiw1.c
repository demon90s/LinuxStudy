// 实验：管理多窗口

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
	WINDOW *new_window_ptr;
	WINDOW *popup_window_ptr;
	int x_loop;
	int y_loop;
	char a_letter = 'a';

	initscr();

	// 用字符填充基本窗口
	move(5, 5);
	printw("%s", "Testing multiple windows");
	refresh();

	for (y_loop = 0; y_loop < LINES - 1; y_loop++) {
		for (x_loop = 0; x_loop < COLS - 1; x_loop++) {
			mvwaddch(stdscr, y_loop, x_loop, a_letter);
			a_letter++;
			if (a_letter > 'z') a_letter = 'a';
		}
	}
	refresh();
	sleep(2);

	// 创建一个尺寸为10*20的新窗口，并添加一些文本
	new_window_ptr = newwin(10, 20, 5, 5);
	mvwprintw(new_window_ptr, 2, 2, "%s", "Hello World");
	mvwprintw(new_window_ptr, 5, 2, "%s", "Notice how very long lines wrap inside the window");
	wrefresh(new_window_ptr);
	sleep(2);

	// 对背景窗口的内容做一些修改，重新刷新时， new_window 将被覆盖掉
	a_letter = '0';
	for (y_loop = 0; y_loop < LINES - 1; y_loop++) {
		for (x_loop = 0; x_loop < COLS - 1; x_loop++) {
			mvwaddch(stdscr, y_loop, x_loop, a_letter);
			a_letter++;
			if (a_letter > '9') a_letter = '0';
		}
	}
	refresh();
	sleep(2);

	// 再刷新一下 new_window ，令其显示
	touchwin(new_window_ptr);
	wrefresh(new_window_ptr);
	sleep(2);

	// 再增加一个重叠的窗口
	popup_window_ptr = newwin(10, 20, 8, 8);
	box(popup_window_ptr, '|', '-');
	mvwprintw(popup_window_ptr, 5, 2, "%s", "Pop Up Window!");
	wrefresh(popup_window_ptr);
	sleep(2);

	// 在清屏和删除这两个窗口之间在屏幕上轮流显示它们
	touchwin(new_window_ptr);
	wrefresh(new_window_ptr);
	sleep(2);
	wclear(new_window_ptr);
	wrefresh(new_window_ptr);
	sleep(2);
	delwin(new_window_ptr);
	touchwin(popup_window_ptr);
	wrefresh(popup_window_ptr);
	sleep(2);
	delwin(popup_window_ptr);
	touchwin(stdscr);
	refresh();
	sleep(2);

	while (1) { sleep(1); }
	endwin();

	return 0;
}

