/*
    #include <sys/types.g>
    #include <dirent.h>

    DIR *opendir(const char* name);
    打开一个目录并建立一个目录流。如果失败返回空指针。
    DIR 结构用于读取目录数据项。

    int closedir(DIR *dirp);
    关闭一个目录流并释放与之关联的资源。成功返回0 。
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    DIR *dirp;

    dirp = opendir("/home");
    if (dirp == NULL) {
        fprintf(stderr, "opendir failed\n");
        return 1;
    }

    printf("open dir succ\n");

    int ret = closedir(dirp);
    if (ret == 0) {
        printf("close dir succ\n");
    }


    return 0;
}