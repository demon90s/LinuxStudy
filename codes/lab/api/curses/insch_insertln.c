/*
	#include <curses.h>

	int insch(chtype char_to_insert);
	int insertln(void);

	insch 插入一个字符，将已有字符向右移，但此操作对行尾的影响未定义，具体情况取决于你所使用的终端。

	insertln插入一个空白行，将现有行依次向下移动一行，光标不变。
*/

#include <curses.h>

void test_insch()
{
	char i;

	move(3, 0);

	for (i = '0'; i <= '9'; i++) {
		insch(i);
	}

	refresh();
}

void test_insertln()
{
	char i;
	move(4, 0);
	for (i = '0'; i <= '9'; i++) {
		addch(i);
		insertln();
	}

	refresh();
}

int main()
{
	initscr();

	test_insch();
	test_insertln();

	endwin();

	return 0;
}
