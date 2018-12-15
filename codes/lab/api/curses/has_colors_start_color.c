/*
	#include <curses.h>

	bool has_colors(void);
	int start_color(void);

	has_colors 检查终端是否支持彩色显示功能

	start_color 对 curses 的颜色例程进行初始，成功返回 OK 。
 */

#include <curses.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	initscr();

	if (!has_colors()) {
		endwin();
		fprintf(stderr, "Error: has_color return false");
		return 1;
	}
	else {
		printw("Init info: this terminal has colors\n");
		refresh();
		sleep(1);
	}

	if (start_color() != OK) {
		endwin();
		fprintf(stderr, "Error: start_color return false");
		return 1;
	}
	else {
		printw("Init info: start color success\n");
		refresh();
		sleep(1);
	}

	pause();
	endwin();

	return 0;
}
