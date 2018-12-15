// 实验：getenv 和 putenv

/*
    实验 getenv 和 putenv

    $ ./emvrion HOME
    $ ./environ FRED
    $ ./environ FRED hello
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *var, *value;

    /* 检查参数 */
    if (argc == 1 || argc > 3) {
        fprintf(stderr, "usage: environ var [value]\n");
        exit(1);
    }

    /* 调用 getenv 从环境中取出变量的值 */
    var = argv[1];
    value = getenv(var);
    if (value)
        printf("Vairable %s has value %s\n", var, value);
    else
        printf("Variable %s has no value\n", var);

    /* 检查是否有第二个参数，如果有，通过构造 "名字=值" 的字符串并调用 putenv 来设置环境变量 */
    if (argc == 3) {
        char *string;
        value = argv[2];
        string = malloc(strlen(var) + strlen(value) + 2);
        if (!string) {
            fprintf(stderr, "out of memory\n");
            exit(1);
        }
        strcpy(string, var);
        strcat(string, "=");
        strcat(string, value);
        printf("Calling putenv with: %s\n", string);
        if (putenv(string) != 0) {
            fprintf(stderr, "putenv failed\n");
            free(string);
            exit(1);
        }
        free(string);

        /* 再次调用 getenv 查看变量的值 */
        value = getenv(var);
        if (value)
            printf("Vairable %s has value %s\n", var, value);
        else
            printf("Variable %s has no value\n", var);
    }

    return 0;
}
