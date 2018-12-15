如果使用到了 terminfo 或者 curses 库，需要：

1. 安装开发包：`yum install ncurses-devel.x86_64`

2. 构建时链接库：-lncurses

terminfo 的功能标志使用 `man terminfo` 查询。
