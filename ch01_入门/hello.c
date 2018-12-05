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
