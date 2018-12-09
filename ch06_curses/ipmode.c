// 实验：键盘模式和输入

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

#define PW_LEN 256
#define NAME_LEN 256

int main()
{
	char name[NAME_LEN];
	char password[PW_LEN];
	const char *real_password = "xyzzy";
	int i = 0;

	initscr();

	move(5, 10);
	printw("%s", "Please login:");

	move(7, 10);
	printw("%s", "User name: ");
	getstr(name);

	move(8, 10);
	printw("%s", "Password: ");
	refresh();

	// 用户输入密码时，不能让密码回显在屏幕上
	cbreak();
	noecho();

	memset(password, '\0', sizeof(password));
	while (i < PW_LEN) {
		password[i] = getch();
		if (password[i] == '\n') {
			password[i] = '\0';
			break;
		}
		move(8, 20 + i);
		addch('*');
		refresh();
		i++;
	}

	// 重启键盘回显，然后验证密码
	echo();
	nocbreak();

	move(11, 10);

	if (strncmp(real_password, password, strlen(real_password)) == 0) {
		printw("%s", "Correct");
	}
	else printw("%s", "Wrong");
	printw("%s", " password");
	refresh();
	sleep(3);

	endwin();

	return 0;
}
