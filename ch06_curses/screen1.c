// 实验：一个Hello World curses程序

#include <unistd.h>
#include <curses.h>

int main()
{
    initscr();

    move(5, 15);
    printw("%s", "Hello World");
    refresh();

    sleep(2);

    endwin();

    return 0;
}