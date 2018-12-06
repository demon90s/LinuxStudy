/*
    #include <stdlib.h>
    char *getenv(const char *var);
    int putenv(const char *string);

    getenv 获取环境变量 var 的值，如果环境变量不存在，那么返回 NULL 。

    putenv 将 string （即一个环境变量的设定 "var=value" ）加入到当前环境中去。如果内存不足，返回-1 ，成功返回0 。
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test_getenv(const char *var)
{
    char *value;
    char *tmp;

    tmp = getenv(var);
    if (!tmp) {
        fprintf(stderr, "getenv failed\n");
        return;
    }

    value = malloc(strlen(tmp) + 1);
    strcpy(value, tmp);

    printf("%s\n", value);

    free(value);
}

void test_putenv()
{
    putenv("FRED=HYHY");

    test_getenv("FRED");
}

int main(int argc, char const *argv[])
{
    test_getenv("HOME");
    test_putenv();

    return 0;
}
