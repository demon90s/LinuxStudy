/*
    #include <curses.h>

    WINDOW *initscr(void);
    int endwin(void);

    所有的 curses 程序必须以 initscr 函数开始，以 endwin 函数结束。

    initscr 在一个程序中只能调用一次。如果成功，返回指向 stdscr 结构的指针，如果失败，就输出诊断错误信息
    并退出程序。

    endwin 成功返回 OK ，失败返回 ERR 。
*/

#include <curses.h>

int main()
{
    initscr();

    printw("Hello curses");
    refresh();

    endwin();

    return 0;
}