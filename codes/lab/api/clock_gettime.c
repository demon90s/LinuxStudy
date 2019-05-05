/*
    <time.h>
    clock_gettime(clockid_t clk_id, const struct timespec *tp);

    获取一个时间, 其意义由 clk_id 决定, 它可以取值:
    - CLOCK_MONOTONIC, 表示系统启动至今的时间
    - CLOCK_REALTIME, 表示系统时钟

    struct timespec {
        time_t tv_sec;          // seconds
        long tv_nsec;           // nanoseconds
    };
*/

#include <time.h>
#include <stdio.h>

int main()
{
    struct timespec ts;
    //clock_gettime(CLOCK_MONOTONIC, &ts);
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("%ld %ld\n", ts.tv_sec, ts.tv_nsec);

    return 0;
}