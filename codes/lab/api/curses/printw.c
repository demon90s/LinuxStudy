/*
	#include <curses.h>

	int printw(char *format, ...);

	采用与 printf 相同的方法对字符串进行格式化，然后将其添加到光标的当前位置。
*/

#include <curses.h>
#include <stdio.h>

void show_line()
{
	int i;

	for (i = 0; i < LINES - 1; i++) {
		char buffer[128];
		sprintf(buffer, "%02d", i + 1);
		move(i, 0);
		printw("%s", buffer);
	}

	refresh();
}

int main() {
	initscr();
	
	show_line();

	endwin();

	return 0;
}
