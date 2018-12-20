/*
    #include <unistd.h>
    int pipe(int file_descriptor[2]);

    创建一个管道。
    函数调用成功返回0 ，并将两个文件描述符填入 file_descriptor ，其中写入 file_descriptor[0] 的数据都可以
    从 file_descriptor[1] 中读出来。数据基于先进先出的原则处理。

    失败返回-1 并设置 errno 。
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <ctype.h>

void test1()
{
    int res;
    int file_descriptor[2];

    res = pipe(file_descriptor);
    if (res == -1) {
        perror("pipe");
        return;
    }

    // 从标准输入读取字符串，然后转大写，写到 file_descriptor[1] ，然后 从 file_descriptor[0] 中读取
    // 以换行符作为终止字符
    {
        char ch;

        printf("write begin\n");
        while ((ch = getchar()) != EOF) {
            ch = toupper(ch);
            write(file_descriptor[1], &ch, 1);
            if (ch == '\n')
                break;
        }
        printf("write end\n");

        printf("read begin\n");
        while (read(file_descriptor[0], &ch, 1) == 1) {
            if (ch == '\n')
                break;
            printf("read - %c\n", ch);
        }
        printf("read end\n");
    }
}

// fork 一个子进程，用管道连接，在子进程中读取，父进程写
void test2()
{
    pid_t child_pid;
    int res;
    int file_descriptor[2];

    res = pipe(file_descriptor);
    if (res == -1) {
        perror("pipe");
        return;
    }

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return;
    }

    {
        char ch;

        if (child_pid > 0) {
            printf("father process(%d) begin\n", getpid());

            while ((ch = getchar()) != EOF) {
                ch = toupper(ch);
                write(file_descriptor[1], &ch, 1);
                if (ch == '\n')
                    break;
            }

            wait(NULL);
            printf("father process(%d) end\n", getpid());
        }
        else {
            printf("child process(%d) begin\n", getpid());
            while (read(file_descriptor[0], &ch, 1) == 1) {
                if (ch == '\n')
                    break;
                printf("read - %c\n", ch);
            }
            printf("child process(%d) end\n", getpid());
        }
    }
}

int main(int argc, char* argv[])
{
    //test1();
    test2();

    return 0;
}