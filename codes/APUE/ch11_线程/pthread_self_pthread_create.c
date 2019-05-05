/*
    这个测试程序创建一个新的线程，打印主线程和新线程的线程ID

    #include <pthread.h>

    pthread_t pthread_self(void);
    返回线程的线程ID

    int pthread_create(pthread_t *tidp,
                        const pthread_attr_t *attr,
                        void *(start_rtn)(void*), void *arg);

    创建一个新线程，成功返回0，否则返回错误编号。
    tidp 传出新线程的线程ID，
    attr 是线程属性，如果为空，则采用默认属性，
    start_rtn 是新线程的启动函数， arg 是启动函数的实参。
*/

#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printtids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
            (unsigned long)tid, (unsigned long)tid);
}

void* thr_fn(void *arg)
{
    printtids("new thread: ");
    return ((void*)0);
}

int main()
{
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0)
        err_exit(err, "can't create thread");

    printtids("main thread: ");

    sleep(1);
    exit(0);
}