/*
 * #include <term.h>
 * #include <curses.h>
 * char *tparm(char *cap, long p1, long p2, ..., long p9);
 * int putp(char *const str);
 * int tputs(char *const str, int affcnt, int (*putfunc)());
 *
 * tparm 用于构造字符串功能标志 cap 的转义序列。将这个序列返回。
 *
 * 然后通过 putp 或 tputs 将序列发送到终端。成功返回 OK ，失败返回 ERR 。
 *
 * putp 将 str 发送到标准输出。
 *
 * tputs 将 str 交给 putfunc 输出，affcnt 作用是表明受这一变化影响的行数，一般设置为1 。
 *
 */

#include <term.h>
#include <curses.h>
#include <stdio.h>

// 清屏
void screen_clear()
{
	putp(tparm(tigetstr("clear")));
}

// 移动光标
void move_cursor()
{
	char *cursor;
	char *esc_sequence;
	cursor = tigetstr("cup");
	esc_sequence = tparm(cursor, 5, 30);
	putp(esc_sequence);

	printf("Hi terminfo\n");
}

int main()
{
	setupterm(NULL, 1, NULL);

	screen_clear();
	move_cursor();

	return 0;
}
