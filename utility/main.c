/*
 * 测试utility中的函数
 */

#include <stdlib.h>
#include "utility.h"

int main(int argc, char* argv[])
{
	copy_file("main.c", "main.c.bak");

	exit(0);
}
