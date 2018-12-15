// 实验：访问空指针

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void a()
{
	char *some_memory = (char*)0;

	printf("A read from null %s\n", some_memory);
	sprintf(some_memory, "A write to null\n");
}

void b()
{
	char z = *(const char*)0;
	(void)z;
	printf("I read from location zero\n");
}

int main()
{
	//a();
	b();

	exit(EXIT_SUCCESS);
}
