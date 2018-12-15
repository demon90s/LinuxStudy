/*
 * 输入和输出重定向（p403）
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char *filename;

	if (argc != 2) {
		fprintf(stderr, "usage: userupper file\n");
		exit(1);
	}

	filename = argv[1];

	// 重新打开标准输入，并再次检查有无错误发生，然后调用execl调用upper程序
	if (!freopen(filename, "r", stdin)) {
		fprintf(stderr, "could not redirect stdin from file %s\n", filename);
		exit(2);
	}

	execl("./upper", "upper", NULL);

	// 不要忘记execl会替换掉当前的进程。如果没有发生错误，剩下的语句将不会被执行
	perror("could not exec ./upper");
	exit(3);
}
