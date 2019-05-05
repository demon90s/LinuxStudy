/*
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>

	int fstat(int fildes, struct stat *buf);
	int stat(const char *path, struct stat *buf);
	int lstat(const char *path, struct stat *buf);

	获取文件的信息。 fstat 根据文件描述符获取， stat 根据文件名，如果文件是一个符号链接， lstat 返回符号链接本身的信息， stat 返回的是指向的文件的信息。
	struct stat 结构一般有：
	st_mode	- 文件权限和文件类型信息
	st_ino - 与该文件关联的 inode
	st_dev - 保存文件的设备
	st_uid - 文件属主的 UID
	st_gid - 文件属主的 GID
	st_atime - 文件上一次被访问的时间
	st_ctime - 文件的权限、属主、组或上一次被改变的时间
	st_mtime - 文件的内容上一次被修改的时间
	st_nlink - 文件的硬链接的个数
	st_size - 以字节为单位的文件大小，只对普通文件、目录和符号链接有效

	使用一些宏可以测试 st_mode ，比如：
	S_ISDIR - 测试文件是一个目录
	S_ISREG - 测试文件是一个普通文件

	成功返回0 ，如果失败返回-1并设置 errno
*/

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

void test1(const char *this_file)
{
	struct stat buf;
	int res = stat(this_file, &buf);
	if (res == -1) {
		perror("stat");
		return;
	}

	int is_reg_file = S_ISREG(buf.st_mode);
	printf("%s is regular file? %s\n", this_file, is_reg_file ? "yes" : "no");
}

void test2(const char* this_file)
{
	struct stat buf;
	int res = stat(this_file, &buf);
	if (res == -1) {
		perror("stat");
		return;
	}

	printf("%s size is; %ld\n", this_file, (long int)buf.st_size);
}

int main(int argc, char *argv[])
{
	//test1(argv[0]);
	test2(argv[0]);
	return 0;
}
