/*
    #include <unistd.h>
    off_t lseek(int fd, off_t offset, int whence);
        成功返回新的文件偏移量（距离文件开始处的）， 出错返回-1.
    
    whence 取值：
    SEEK_SET, 此时 offset 意思是距离文件开始处 offset 个字节
    SEEK_CUR, 此时 offset 意思是距离当前位置处 offset 个字节
    SEEK_END, 此时 offset 意思是距离文件末尾处 offset 个字节
*/

#include "apue.h"
#include "fcntl.h"

/*
    像管道、套接字, 标准输出(没有重定向)这样的文件不可以设置偏移量， 
    lseek 会返回-1，errno 会设置成 ESPIPE.

    try:
    ./lseek
    ./lseek < ./build.sh
*/
void test1()
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        perror("cannot seek stdin");
    else
        printf("seek stdin ok\n");
}

/*
    文件的偏移量可以大于文件的长度，此时写操作会造成一个空洞。读取它将返回0.
    文件的空洞不会占用存储区。但新写的数据会分配磁盘块。

    try:
    查看文件内容： od -c file.hole
    查看文件磁盘块：ls -ls file.hole
*/
void test2()
{
    const char buf1[] = "abcdefj";
    const char buf2[] = "ABCDEFJ";

    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("create error");

    if (write(fd, buf1, 7) != 7)
        err_sys("buf1 write error");
    /* offset now is 7 */

    if (lseek(fd, 10000, SEEK_SET) == -1)
        err_sys("lseek error");
    /* offset now is 10000 */

    if (write(fd, buf2, 7) != 7)
        err_sys("buf2 write error");
    /* offset now is 10007 */
}

int main()
{
    /*test1();*/
    test2();
    return 0;
}
