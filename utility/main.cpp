/*
 * 测试utility中的函数
 */

#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "utility.h"
#include "ProcessFork.h"
#include "StringTrans.h"

using namespace utility;

int main(int argc, char* argv[])
{
	//CopyFile("main.c", "main.c.bak");
	Execute("ps aux");
	
	//Test_ProcessFork();
	//Test_StringTrans();

	exit(0);
}
