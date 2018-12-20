/*
	#include <curses.h>

	int beep(void);
	int flash(void);

	beep 发出一声鸣叫。
	flash 使得终端闪烁一下。

	PS: 经过测试，即使不调用 refresh 也能起效果。
*/

#include <curses.h>
#include <unistd.h>

void test_beep_flash()
{
	while (1) {
		beep();
		flash();
		//refresh();

		sleep(1);
	}
}

int main()
{
	initscr();

	test_beep_flash();

	endwin();

	return 0;
}
