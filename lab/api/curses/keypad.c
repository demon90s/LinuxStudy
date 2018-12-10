/*
	#include <curses.h>

	int keypad(WINDOW *window_ptr, bool keypad_on);

	curses 通过一组以 KEY_ 为前缀的定义来管理逻辑键（比如上下左右按键）

	curses 启动时，会关闭转义序列与逻辑键之间的功能，通过 keypad 函数来打开。

	函数成功返回 OK ，失败返回 ERR
 */

#include <curses.h>
#include <ctype.h>

int main()
{
	int ch;

	initscr();

	noecho();
	keypad(stdscr, 1);
	do {
		ch = getch();
		if (isalnum(ch)) {
			clear();
			mvprintw(0, 0, "you enter: %c", ch);
			refresh();
		}
		else {
			clear();
			switch(ch) {
				case KEY_UP: mvprintw(0, 0, "you enter up key"); break;
				case KEY_DOWN: mvprintw(0, 0, "you enter down key"); break;
				case KEY_LEFT: mvprintw(0, 0, "you enter left key"); break;
				case KEY_RIGHT: mvprintw(0, 0, "you enter right key"); break;
				default: mvprintw(0, 0, "you enter Other logic key(%d)", ch); break;
			}
			refresh();
		}
	} while (ch != 'q' && ch != ERR);


	endwin();

	return 0;
}
