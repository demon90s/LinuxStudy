/*
 * #include <term.h>
 * #include <curses.h>
 * int setupterm(char *term, int fd, int *errret);
 *
 * 设置一个终端类型为 term ，如果 term 是 NULL ，那么设置的就是环境变量 TERM 的值。
 *
 * fd 是一个打开的文件描述符，用于向终端写数据。
 *
 * 如果 errret 不是空指针，则把调用结果保存到它里面，否则，如果设置失败，程序输出诊断信息后，终止运行。
 *
 * 函数返回OK（0）表示成功，ERR(-1)表示失败。
 */

#include <term.h>
#include <curses.h>
#include <stdio.h>

void print_OK_ERR()
{
	printf("value of OK: %d\n", OK);
	printf("value of ERR: %d\n", ERR);
}

void test_setupterm_failed()
{
	char* err_desc[3] = {
		"terminfo数据库不存在",
		"terminfo数据库中没有匹配项",
		"成功"
	};

	int errret;
	int ret = setupterm("nolisted", 1, &errret);
	if (ret == OK) {
		printf("setupterm succ.\n");
	}
	else {
		fprintf(stderr, "setupterm failed(%d): %s\n", errret, err_desc[errret + 1]);
	}
}

void test_setupterm_default()
{
	setupterm(NULL, 1, NULL);
}

int main()
{
	//print_OK_ERR();

	//test_setupterm_failed();
	test_setupterm_default();

	printf("Done.\n");
	return 0;
}
