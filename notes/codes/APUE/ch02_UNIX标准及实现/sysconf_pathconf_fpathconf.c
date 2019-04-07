/*
    #include <unistd.h>
    long sysconf(int name);
    long pathconf(const char *pathname, int name);
    long fpathconf(int fd, int name);
            成功返回相应值，失败返回-1

    这些函数用来或许系统的运行时限制的值。
    sysconf 获得的值与文件与路径无关，pathconf fpathconf 有关。

    name 用于标识系统限制，_SC_开始的常量用于 sysconf, _PC_开始的用于 pathconf fpathconfig
    具体的内容可以参考书本p34
*/

#include "apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char*, int);
static void pr_pathconf(char*, char*, int);

int main(int argc, char **argv)
{
    if (argc != 2) {
        err_quit("usage: %s <dirname>", argv[0]);
    }

    /* sysconf */
    #ifdef ARG_MAX
        printf("ARG_MAX defined to be %ld\n", (long)ARG_MAX);
    #else
        printf("no symbol for ARG_MAX\n");
    #endif
    #ifdef _SC_ARG_MAX
        pr_sysconf("ARG_MAX =", _SC_ARG_MAX);
    #else
        printf("no symbol for _SC_ARG_MAX\n");
    #endif

    /* pathconf */
    #ifdef MAX_CANON
        printf("MAX_CANON defined to be %ld\n", (long)MAX_CANON);
    #else
        printf("no symbol for MAX_CANON\n");
    #endif
    #ifdef _PC_MAX_CANON
        pr_pathconf("MAX_CANON =", argv[1], _PC_MAX_CANON);
    #else
        printf("no symbol for _PC_MAX_CANON\n");
    #endif

    return 0;
}

static void
pr_sysconf(char *mesg, int name)
{
    long val;

    fputs(mesg, stdout);
    errno = 0;
    if ((val = sysconf(name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL)
                fputs(" (not supported)\n", stdout);
            else
                err_sys("sysconf error");
        }
        else {
            fputs(" (no limit)\n", stdout);
        }
    }
    else {
        printf(" %ld\n", val);
    }
}

static void
pr_pathconf(char *mesg, char* path, int name)
{
    long val;

    fputs(mesg, stdout);
    errno = 0;
    if ((val = pathconf(path, name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL)
                fputs(" (not supported)\n", stdout);
            else
                err_sys("pathconf error, path = %s", path);
        }
        else {
            fputs(" (no limit)\n", stdout);
        }
    }
    else {
        printf(" %ld\n", val);
    }
}