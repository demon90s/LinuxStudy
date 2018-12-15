/*
    #include <curses.h>

    int addch(const chtype char_to_add);
    int addchstr(chtype *const string_to_add);

    chtype 是 curses 自己的字符类型，在 Linux 版本中，实际上是 unsigned long 。

    addch 在光标位置添加一个字符 char_to_add 。
    addchstr 在光标位置添加一个字符从 string_to_add 。

    函数成功返回 OK ，失败返回 ERR 。
*/

#include <curses.h>

void test1()
{
    move(5, 5);
    addch('X');
    move(6, 5);

    chtype str[] = {
        'O', 'U', 'C', 'H', '!', 0
    };
    addchstr(str);

    refresh();
}

int main()
{
    initscr();

    test1();

    endwin();

    return 0;
}
