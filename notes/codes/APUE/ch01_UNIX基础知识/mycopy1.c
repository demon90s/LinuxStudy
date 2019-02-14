#include "apue.h"

#define BUFFSIZE 4096

/* ./mycopy1 > somefile */
int
main(int argc, char *argv[])
{
    char buffer[BUFFSIZE];
    int n;

    while ((n = read(STDIN_FILENO, buffer, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, n) < 0)
            err_sys("write error");
    }

    if (n < 0)
        err_sys("read error");

    exit(0);
}