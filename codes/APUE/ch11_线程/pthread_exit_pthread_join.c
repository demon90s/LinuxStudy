/*
void pthread_exit(void *rval_ptr);
退出线程，并指定返回值为 rval_ptr, 这个指针通过 pthread_join 得到。
注意：rval_ptr 所指向的内存必须在线程结束后仍然有效。

int pthread_join(pthread_t thread, void **rval_ptr);
阻塞地等待 thread 结束， 其返回值保存到 rval_ptr 中。
成功返回0，失败返回错误编号。
失败的原因可能是 thread 已经处于分离状态。
如果对返回值不感兴趣，可以把 rval_ptr 设置为 NULL 。
*/

#include "apue.h"
#include <pthread.h>

void*
thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return ((void*)1);
}

void*
thr_fn2(void *arg)
{
    printf("thread 2 returning\n");
    return ((void*)2);
}

int
main()
{
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        err_exit(err, "can't create thread 1");

    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        err_exit(err, "can't create thread 2");

    err = pthread_join(tid1, &tret);
    if (err != 0)
        err_exit(err, "can't join with thread 1");
    printf("thread 1 exit code %ld\n", (long)tret);

    err = pthread_join(tid2, &tret);
    if (err != 0)
        err_exit(err, "can't join with thread 2");
    printf("thread 2 exit code %ld\n", (long)tret);

    return 0;
}