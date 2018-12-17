/*
    #include <sys/types.h>
    #include <unistd.h>

    pid_t fork(void);

    创建一个新的子进程，执行的代码完全一样，但新进程有自己的数据空间，环境和文件描述符。
    函数返回子进程的 PID ，子进程返回 0 。
    失败返回-1 ，并设置 errno 。

    my note:
        子进程可以继承在父进程中打开了的文件描述符的拷贝。也就是说，子进程在创建后也打开了相同数量的文件描述符。
*/

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void test1()
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return;
    }

    if (child_pid > 0) {
        printf("father process(%d) begin\n", getpid());
        wait(NULL);
        printf("father process(%d) end\n", getpid());
    }
    else {
        printf("child process(%d) begin\n", getpid());
        sleep(2);
        printf("child process(%d) end\n", getpid());
    }
}

int main(int argc, char* argv[])
{
    test1();
    return 0;
}