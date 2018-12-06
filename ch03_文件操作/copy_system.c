// 实验：一个文件复制程序

/*
 * 一个文件复制程序
 * 此版本用来逐个字符地把一个文件复制到另一个文件，为简单起见，我们将假设
 * 输入文件已经存在，输出文件不存在，并且所有读写操作都成功。
 *
 * note: 创建一个1MB的空文件的命令（见http://man.linuxde.net/dd）：
 * $ dd if=/dev/zero of=file.in bs=1M count=1
 *
 * 编译命令：
 * $ gcc -o copy_system copy_system.c
 *
 * 运行命令（查看运行时间）：
 * $ TIMEFORMAT="" time ./copy_system
 */

#include <unistd.h>	// 必须首行出现，因为它定义的与POSIX规范有关的标志可能会影响到其他的头文件
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	char c;
	int in, out;

	in = open("file.in", O_RDONLY);
	out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while (read(in, &c, 1) == 1)
		write(out, &c, 1);

	exit(0);
}
