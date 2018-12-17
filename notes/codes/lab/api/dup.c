/*
    #include <unistd.h>

    int dup(int file_descriptor);

    打开一个新的文件描述符，返回的文件描述符与 file_descriptor 指向同一个文件。
    新的文件描述符总是取最小的可用值。

    失败返回-1 并设置 errno 。
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void test1()
{
    int fd;
    int new_fd;

    fd = open("/tmp/test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return;
    }

    // 关掉标准输出，令文件描述符1指向刚才打开的文件
    close(1);
    new_fd = dup(fd);

    // 之后，像使用标准输出一样写文件
    printf("You do not known I am from standard input...(output fd is %d)\n", new_fd);
    fflush(stdout);

    // 也可以通过文件描述符写到文件
    {
        char buffer[1024];
        sprintf(buffer, "Right, real output fd is %d\n", fd);
        write(fd, buffer, strlen(buffer));
    }
}

int main(int argc, char* argv[])
{
    test1();

    return 0;
}