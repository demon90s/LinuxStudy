// 实验：用C语言编写的菜单例程（检查是否存在输出重定向）

// 如果使用这样的命令启动程序，程序将直接退出：
//
// $ ./menu2 > log

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greet, char *choices[]);
void checktty();

int main()
{
	checktty();

	int choice = 0;

	do {
		choice = getchoice("Please select an action", menu);
		printf("You have chosen: %c\n", choice);

	} while (choice != 'q');

	return 0;
}

// 检查标准输出是否连接了终端，没有就终止程序
void checktty()
{
	if (!isatty(fileno(stdout))) {
		fprintf(stderr, "You are not a terminal!\n");
		exit(1);
	}
}

// 程序核心代码，负责显示菜单及读取用户输入
int getchoice(char *greet, char *choices[])
{
	int chosen = 0;
	int selected;
	char **option;

	do {
		printf("Choice: %s\n", greet);
		option = choices;
		while (*option) {
			printf("%s\n", *option);
			option++;
		}

		selected = getchar();
		while (getchar() != '\n');

		option = choices;
		while (*option) {
			if (selected == *option[0]) {
				chosen = 1;
				break;
			}
			option++;
		}
		if (!chosen) {
			printf("Incorrect choice, select again!\n");
		}

	} while (!chosen);

	return selected;
}
