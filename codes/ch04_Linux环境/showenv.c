// 实验：environ 变量

/*
    实验 environ 变量

    #include <stdlib.h>
    extern char **environ;

    这是一个字符串数组( NULL 结尾)，存放了的是环境变量的设定： "var=vale"
*/

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
