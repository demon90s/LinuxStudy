// 实验：程序参数

/*
 * 程序参数（p115）
 * 
 * use:
 * $ ./args -i -lr 'hi there' -f fred.c
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int arg;

	for (arg = 0; arg < argc; arg++) {
		if (argv[arg][0] == '-')
			printf("option: %s\n", argv[arg]+1);
		else
			printf("argument %d: %s\n", arg, argv[arg]);
	}

	exit(0);
}
