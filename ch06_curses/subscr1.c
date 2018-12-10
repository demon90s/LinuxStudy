// 实验：子窗口

// 子窗口和一个新窗口的不同就在于它与父窗口共享字符存储空间（会影响父窗口的内容）

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
	WINDOW *sub_window_ptr;
	int x_loop;
	int y_loop;
	int counter;

	char a_letter = '1';

	initscr();

	for (y_loop = 0; y_loop < LINES-1; y_loop++) {
		for (x_loop = 0; x_loop < COLS-1; x_loop++) {
			mvwaddch(stdscr, y_loop, x_loop, a_letter);
			a_letter++;
			if (a_letter > '9') a_letter = '1';
		}
	}

	// 创建一个新的子窗口，可卷动。必须在刷新屏幕之前对父窗口调用 touchwin
	sub_window_ptr = subwin(stdscr, 10, 20, 10, 10);
	scrollok(sub_window_ptr, 1);

	touchwin(stdscr);
	refresh();
	sleep(1);

	// 删除子窗口中的内容，重新输出一些文字，然后滚动文本
	werase(sub_window_ptr);
	mvwprintw(sub_window_ptr, 2, 0, "%s", "This window will now scroll");
	wrefresh(sub_window_ptr);
	sleep(1);

	for (counter = 1; counter < 10; counter++) {
		wprintw(sub_window_ptr, "%s", "This text is both warpping and scrolling.");
		wrefresh(sub_window_ptr);
		sleep(1);
	}

	// 删除子窗口，再次刷新，内容不会变化
	delwin(sub_window_ptr);
	touchwin(stdscr);
	refresh();
	sleep(2);

	endwin();

	return 0;
}
