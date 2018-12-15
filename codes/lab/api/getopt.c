/*
    #include <unistd.h>

    int getopt(int argc, char *const argv[], const char *optstring);
    extern char *optarg;
    extern int optind, opterr, optopt;

    提供了获取程序运行参数的方法。 Linux 有一个编程的准则，把 - 开头的参数叫做选项（ option ），
    普通的参数叫做选项的值（跟在选项的后面， argument ）。

    getopt 就是为了帮我们遵循这一个准则而创造的。

    将 main 函数的 argc 和 argv 传递给 getopt 调用， optstring 告诉了函数哪些选项可用。
    optstring 比如是 "if:l" ，那么它支持选项 -i -f -l ，且 -f 后面要跟着一个关联值，因为它后面有一个 :

    每次调用，函数返回 argv 中 下一个选项字符，如果处理完毕，返回 -1 。特殊参数 -- 将使 getopt 停止扫描。
    如果选项无法识别，返回一个 ? ，并把这个选项保存到 optopt 中。
    如果选项有一个关联值，则外部变量 optarg 指向这个值。
    如果一个选项要求关联值，却未提供，那么通常返回 ? ，但，如果 optstring 第一个字符是 : ，那么这种情况下，返回的是 : ，并把这个选项保存到 optopt 中。

    optind 被设置为下一个 argv 中待处理参数的索引，由于函数会修改 argv ，因此调用返回-1后， argv[optind] 指向的是其余未处理的参数。 
*/

/*
    关于重写 argv 数组：
    有些版本的 getopt 会在 argv 中第一个非选项参数处停下来，然后返回 -1 。而有的版本更加灵活，参数可以出现在任意位置，这种情况，就会修改 argv 数组，
    把所有非选项参数集中在一起（最后），从 argv[optind] 位置开始。
*/

/*
    有些 getopt 版本还会在遇到未知选项时打印出错信息。根据 POSIX 规定，如果 opterr 变量是非零值， getopt 会向 stderr 打印一条出错消息。
*/

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    /*
        可接受选项：
        -h
        -f <argument>
        -o
    */
    const char *optstring = ":hf:o";
    char opt;

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch(opt) {
            case '?' : 
                printf("unknown options[%c]\n", optopt);
                break;
            case ':' :
                printf("option %c need an argument\n", optopt);
                break;
            case 'h':
                printf("***option h matched***\n");
                break;
            case 'o':
                printf("***option o matched***\n");
                break;
            case 'f':
                printf("***option f matched with value %s***\n", optarg);
                break;
        }
    }

    printf("---------other argument:\n");
    for (; optind < argc; optind++)
		printf("argument: %s\n", argv[optind]);
    
    return 0;
}
