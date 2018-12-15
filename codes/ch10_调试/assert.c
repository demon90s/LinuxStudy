// 实验：assert

// 加入编译选项 -DNDEBUG 可以关掉 assert 宏

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double my_sqrt(double x)
{
	assert(x >= 0.0);
	return sqrt(x);
}

int main()
{
	printf("sqrt +2 = %g\n", my_sqrt(2.0));
	printf("sqrt -2 = %g\n", my_sqrt(-2.0));
	exit(0);
}
