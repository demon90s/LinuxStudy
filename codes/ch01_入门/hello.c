// 实验：第一个Linux C语言程序

/*
 * 第一个Linux程序，著名的Hello World程序。
 * $ gcc -o hello hello.c
 * $ ./hello
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("Hello World\n");

	exit(0);
}
