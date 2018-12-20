/*
	#include <curses.h>

	int init_pair(short pair_number, short foreground, short background);
	int COLOR_PAIR(int pair_number);

	curses 必须同时定义个字符的前景色和背景色，称为颜色组合 color pair 。

	init_pair 为 pair_number 设置一个 color pair ， pair_number 要从1开始。
	COLOR_PAIR 使用 pair_number 生成一个字符属性，然后可以使用 attrset 来设置。

	foreground 和 background 可以使用 COLOR_XXX 来取值，比如 COLOR_RED
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	initscr();

	start_color();

	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	attrset(COLOR_PAIR(1));
	printw("Wow~~~~~~");
	refresh();

	pause();

	endwin();

	return 0;
}
