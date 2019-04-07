/*
    条件变量, 可用于线程同步. 它阻塞住线程, 等待另一个线程激活此条件变量, 然后被唤醒

    int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
    初始化条件变量 cond, cond_attr 可以是 NULL 保存默认.

    int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
    并阻塞等待条件变量为真

    int pthread_cond_timewait(pthread_cond_t *cond, pthread_mutex *mutex, const timespec *abstime);
    阻塞等待一段时间, 如果时间到了条件变量还未被激活, 那么返回 ETIMEOUT

    int pthread_cond_signal(pthread_cond_t *cond);
    激活某一个线程的条件变量.

    int pthread_cond_broadcast(pthread_cond_t *cond);
    为所有的线程激活条件变量

    int pthread_cond_destroy(pthread_cond_t *cond);
    清除条件变量.

    这些函数成功返回0, 错误返回错误编号.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t cond_mutex;
pthread_cond_t cond;

void *thread(void *arg)
{
    int applied_cond = 0;
    const char *thread_name = (const char*)arg;

    printf("%s is running\n", thread_name);

    while (1) {
        pthread_mutex_lock(&cond_mutex);
        pthread_cond_wait(&cond, &cond_mutex);
        applied_cond = 1;
        pthread_mutex_unlock(&cond_mutex);

        if (applied_cond) {
            printf("%s applied the condition\n", thread_name);
            break;
        }

        sleep(1);
    }

    printf("%s is end\n", thread_name);

    return 0;
}

int main()
{
    pthread_t tid1, tid2;

    pthread_mutex_init(&cond_mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tid1, NULL, thread, "thread1");
    pthread_create(&tid2, NULL, thread, "thread2");

    printf("main thread will signal cond after 3 seconds...\n");
    sleep(3);
    //pthread_cond_signal(&cond);
    //pthread_cond_signal(&cond); // for two thread
    pthread_cond_broadcast(&cond);  // for all thread

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&cond_mutex);

    return 0;
}