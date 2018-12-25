/*
    #include <sys/types.h>
    #include <dirent.h>

    struct dirent *readdir(DIR *dirp);

    读取目录流中的一个目录项。后续的调用将返回后续的目录项，如果发生错误或到达目录尾，返回 NULL 。
    发生错误才会设置 errno 。

    struct dirent 结构包含：
    ino_t d_ino - 文件的 inode 节点
    char d_name[] - 文件的名字
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main()
{
    DIR *dirp = opendir(".");
    if (dirp == NULL) {
        fprintf(stderr, "opendir failed");
        return 1;
    }

    // 输出所有的文件
    struct dirent *dirent_data;
    while ((dirent_data = readdir(dirp)) != NULL) {
        printf("%s\n", dirent_data->d_name);
    }

    closedir(dirp);

    return 0;
}