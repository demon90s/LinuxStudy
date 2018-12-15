/*
    #define _GNU_SOURCE
    #include <getopt.h>
    int getopt_long(int argc, char* const argv[],
                    const char* optstring,
                    const struct option *longopts,
                    int *longindex);

    功能和 getopt 一样，只不过附加了一些功能，支持了长选项，即如同 --help 或 --file=foo.c 这样的选项。甚至 --h 也可以表示 --help （只要能区分）。

    longopts 告诉了长选项的信息：
    struct option {
        const char* name;   // 长选项的名字
        int has_arg;        // 0表示不带参数，1代表有一个参数，2代表有一个可选参数，如果实际上没参数，那么结果为 (null)
        int *flag;          // 当匹配时，影响 getopt_long 的返回值，如果为 NULL ，则函数返回 val 的值，否则函数返回0，并将 val 的值写入 flag 空间
        int val;            // 如上所属，作为 getopt_long 的返回值
    };
    longopts 数组必须以{0,0,0,0}结尾。

    longindex 如果非 NULL ，则每次调用后把当前 longopts 数组的索引写入。
*/

#include <unistd.h>
#include <stdio.h>

#define _GNU_SOURCE
#include <getopt.h>

int main(int argc, char *argv[])
{
    /*
        可接受选项：
        --help
        -h
        --file=argument
        -f <argument>
        --option [可选参数]
        -o
    */
    const char *optstring = ":hf:o";
    struct option longopts[] = {
        {"help", 0, NULL, 'h'},
        {"file", 1, NULL, 'f'},
        {"opt", 2, NULL, 'o'},
        {0, 0, 0, 0},
    };
    int longindex;
    char opt;

    longindex = -1;
    while ((opt = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1) {
        switch(opt) {
            case '?' : 
                printf("unknown options[%c]\n", optopt);
                break;
            case ':' :
                printf("option %c need an argument\n", optopt);
                break;
            case 'h':
                if (longindex != -1)
                    printf("***option %s matched***\n", longopts[longindex].name);
                else
                    printf("***option h matched***\n");
                break;
            case 'o':
                if (longindex != -1)
                    printf("***option %s matched with value %s***\n", longopts[longindex].name, optarg);
                else
                    printf("***option o matched***\n");
                break;
            case 'f':
                if (longindex != -1)
                    printf("***option %s matched with value %s***\n", longopts[longindex].name, optarg);
                else
                    printf("***option f matched with value %s***\n", optarg);
                break;
        }
        longindex = -1;
    }

    printf("---------other argument:\n");
    for (; optind < argc; optind++)
		printf("argument: %s\n", argv[optind]);
    
    return 0;
}