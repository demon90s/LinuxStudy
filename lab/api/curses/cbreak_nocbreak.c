/*
	#include <curses.h>

	int cbreak(void);
	int nocbreak(void);

	设置键盘读取模式为预处理模式/cbreak模式。

	预处理模式是基于行的，当按下回车键的时候，输入的数据才会被传送给程序。

	如果是 cbreak 模式，字符一经键入就传递给程序。
 */

#include <curses.h>
#include <unistd.h>

int main()
{
	int ch;

	initscr();

	printw("nocbreak mode, press enter to confirm.\n");
	nocbreak();
	ch = getch();
	printw("You enter: %c\n", ch);
	refresh();

	/* consume left characters... */
	while (getch() != '\n');

	printw("cbreak mode, no need to press enter button.\n");
	cbreak();
	ch = getch();
	printw("You enter: %c\n", ch);
	refresh();

	sleep(3);

	endwin();

	return 0;
}
