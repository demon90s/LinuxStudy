#include "apue.h"

/* getpid 函数获得进程ID ，它是一个 pid_t 类型的数据，标准会保证它能存储在一个长整型中。*/

int
main(int argc, char *argv[])
{
    printf("Hello world from process ID %ld\n", (long)getpid());

    exit(0);
}