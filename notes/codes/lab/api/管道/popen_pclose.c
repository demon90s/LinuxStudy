/*
	#include <stdio.h>

	FILE *popen(const char* command, const char *open_mode);
	int pclose(FILE *stream_to_close);

	popen 使用 command 开启一个新进程， open_mode 必须是 "r" 或者 "w" ，表示从被调用进程读取其标准输出，或者写给被调用进程的标准输入。
	返回值就是用来操作这种流的。
	函数失败返回空指针。

	pclose 关闭与被调用进程关联的文件流， pclose 调用只在启动进程结束后才返回。如果调用 pclose 时它仍然在运行，那么将等待。

	pclose 调用的返回值通常是被调用进程的退出码。
	如果在调用 pclose 前执行了一个 wait 语句，被调用进程的退出状态就会丢失，此时 pclose 返回-1并设置 errno 为 ECHILD 。

	my note:
	- 被打开的进程是一个子进程。
	- 管道的刷新需要调用 fflush。
	- 流被关闭也会刷新管道。
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// 测试启动一个进程，读取它的标准输出
void func1()
{
	FILE *fp;

	printf("func1 call ping to read\n");

	fp = popen("ping -c 5 www.bing.com", "r");
	if (fp == NULL) {
		fprintf(stderr, "popen failed\n");
	}

	// read
	{
		char buffer[BUFSIZ];
		while (fgets(buffer, sizeof(buffer), fp)) {
			printf("%s", buffer);
		}
	}

	pclose(fp);

	printf("func1 stopped\n");
}

// 测试启动一个进程，向其标准输入写内容
void func2()
{
	FILE *fp;

	printf("func2 call cat to write\n");

	fp = popen("od -c", "w");
	if (fp == NULL) {
		fprintf(stderr, "popen failed\n");
	}

	// write
	{
		char buffer[1024];
		sprintf(buffer, "hello\n");
		fwrite(buffer, sizeof(char), strlen(buffer), fp);
	}

	pclose(fp);

	printf("func2 stopped\n");
}

// 选择性启动俩进程，一个读，一个写
// 读进程单纯地以为自己从标准输入读
// 写进程会打开读进程，给他输送内容
void echo(int argc, char** argv)
{
	char *cmd;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./popen_pclose <write|read>\n");
		return;
	}
	cmd = argv[1];

	if (strcmp(cmd, "write") == 0) {
		FILE *fp;
		printf("write process begin\n");
		fp = popen("./popen_pclose read", "w");
		if (NULL == fp) {
			fprintf(stderr, "popen failed\n");
			return;
		}

		{
			char buffer[BUFSIZ];
			while (fgets(buffer, sizeof(buffer), stdin)) {
				int i;
				for (i = 0; i < strlen(buffer); i++)
					buffer[i] = toupper(buffer[i]);
				fputs(buffer, fp);
				fflush(fp); // 必须调用，否则不会刷新管道
			}
		}

		pclose(fp);
		printf("write process end\n");
	}
	else if (strcmp(cmd, "read") == 0) {
		char buffer[4096];

		printf("read process begin\n");

		while (fgets(buffer, sizeof(buffer), stdin)) {
			printf("read - %s", buffer);
		}
		printf("read process end\n");
	}
}

int main(int argc, char* argv[])
{
	//func1();
	//func2();
	echo(argc, argv);

	return 0;
}
