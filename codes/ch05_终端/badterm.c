/*
 * 测试 setupterm 函数，这里字符串 Done 不会输出，因为 setupterm 函数会在执行失败时导致程序直接退出
 */

#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	setupterm("unlisted", fileno(stdout), (int*)0);
	printf("Done.\n");

	return 0;
}
