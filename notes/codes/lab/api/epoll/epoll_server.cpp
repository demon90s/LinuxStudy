/*
    epoll 是一种 IO 多路复用模型的实现。

    它使用一个文件描述符管理多个文件描述符。

    #include <sys/epoll.h>
    int epoll_create(int size);
    int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

    epoll_create 创建 epoll 文件描述符，为后续的 api 的第一个参数。 size 是告诉内核要监听的文件描述符数量。

    epoll_ctl 用来增加、修改、删除在 fd 上监听的事件类型。
    op 的取值可以是： EPOLL_CTL_ADD, EPOLL_CTL_MOD, EPOLL_CTL_DEL 。
    struct epoll_event {
        __unit32 events;        // 可取值 EPOLLIN 读, EPOLLOUT 写 ...
        epoll_data_t data;      // user data, 有一个成员 fd
    };

    epoll_wait 等待事件的产生， events 从内核得到事件的集合， maxevents 告诉内核这个 events 有多大， 
    timeout 是毫秒级别的超时时间，如果取值-1代表阻塞等待。
    函数返回需要处理的事件数目，返回0代表超时。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#define IPADDRESS "127.0.0.1"
#define PORT 6666
#define MAXSIZE 1024
#define LISTENQ 5
#define FDSIZE 1000
#define EPOLLEVENTS 100

/* 添加事件 */
void add_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

/* 删除事件 */
void delete_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

/* 修改事件 */
void modify_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

/* 读处理 */
void do_read(int epollfd, int fd, char *buf)
{
    int nread;
    nread = read(fd, buf, MAXSIZE);
    if (nread == -1) {
        perror("read");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else if (nread == 0) {
        fprintf(stderr, "client close.\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    else {
        printf("read msg is: %s\n", buf);
        modify_event(epollfd, fd, EPOLLOUT);
    }
}

/* 写处理 */
void do_write(int epollfd, int fd, char *buf)
{
    int nwrite;
    nwrite = write(fd, buf, strlen(buf));
    if (nwrite == -1) {
        perror("write");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    }
    else {
        modify_event(epollfd, fd, EPOLLIN);
    }

    memset(buf, 0, sizeof(MAXSIZE));
}

/* 创建套接字并进行绑定 */
int socket_bind(const char* ip, int port)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error");
        exit(1);
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IPADDRESS);
    servaddr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    printf("[DEBUG] socket_bind on %s:%d\n", ip, port);

    return listenfd;
}

/* 处理接收到的连接 */
void handle_accept(int epollfd, int listenfd)
{
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    clifd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
    if (clifd == -1) {
        perror("accept");
    }
    else {
        printf("accept a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        add_event(epollfd, clifd, EPOLLIN);
    }
}

/* 事件处理函数 */
void handle_events(int epollfd, struct epoll_event *events, int num, int listenfd, char *buf)
{
    for (int i = 0; i < num; ++i) {
        int fd = events[i].data.fd;
        int ev = events[i].events;

        if ((fd == listenfd) && (ev & EPOLLIN)) {
            handle_accept(epollfd, listenfd);
        }
        else if (ev & EPOLLIN) {
            do_read(epollfd, fd, buf);
        }
        else if (ev & EPOLLOUT) {
            do_write(epollfd, fd, buf);
        }
    }
}

/* IO 多路复用 epoll */
void do_epoll(int listenfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    memset(buf, 0, MAXSIZE);

    epollfd = epoll_create(FDSIZE);

    add_event(epollfd, listenfd, EPOLLIN);

    while (true) {
        int ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handle_events(epollfd, events, ret, listenfd, buf);
    }
}

int main()
{
    int listenfd;
    listenfd = socket_bind(IPADDRESS, PORT);
    if ((listen(listenfd, LISTENQ) == -1)) {
        perror("listen");
        return 1;
    }

    printf("[DEBUG] listen on %s:%d\n", IPADDRESS, PORT);

    do_epoll(listenfd);

    return 0;
}