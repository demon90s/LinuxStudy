// 实验：另一个文件复制程序（块复制）

/*
 * 另一个文件复制程序
 * 通过复制大一些的数据块来改善效率较低的问题
 *
 * 编译命令：
 * $ gcc -o copy_block copy_block.c
 *
 * 执行命令（查看运行时间）：
 * $ TIMEFORMAT="" time ./copy_block
 */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char block[1024];
	int in, out;
	int nread;

	in = open("file.in", O_RDONLY);
	out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while ((nread = read(in, block, sizeof(block))) > 0)
		write(out, block, nread);

	exit(0);
}
