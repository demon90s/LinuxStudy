/*
 * #include <term.h>
 *
 * int tigetflag(char *capname);
 * int tigetnum(char *capname);
 * char* tigetstr(char *capname);
 *
 * 获取 terminfo 的功能标志 capname 的值，flag 是获取布尔功能标志，num 是获取数值功能标志，str 是获取字符串功能标志。
 *
 * 如果 capname 不存在，tigetflag 返回-1 ， tigetnum 返回-2 ， tigetstr 返回 (char*)-1 。
 *
 * 通过呼叫 man terminfo 查询这些标志和说明。
 */

#include <term.h>
#include <stdio.h>

// 显示终端的长和宽
void show_term_row_col()
{
	int nrows, ncols;

	setupterm(NULL, fileno(stdout), NULL);
	nrows = tigetnum("lines");
	ncols = tigetnum("cols");

	printf("terminal size: rows[%d], cols[%d]\n", nrows, ncols);
}

int main()
{
	show_term_row_col();

	return 0;
}
