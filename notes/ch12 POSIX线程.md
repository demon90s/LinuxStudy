# 第十二章 POSIX线程

有时人们认为，用fork调用来创建新进程的代价太高。在这种情况下，如果能让一个进程同时做两件事情或至少看起来是这样将会非常有用。而且，你可能希望有两件或更多的事情以一种非常紧密的方式同时发生。这就是需要线程发挥作用的时候了。

---

## 什么是线程

在一个程序中的多个执行路线就叫做线程（thread）。更准确的定义是：线程是一个进程内部的一个控制序列。事实上，所有的进程都至少有一个执行线程。

当进程调用fork时，将创建出该进程的一份副本。这个新进程拥有自己的变量和自己的PID，它的时间调度是独立的，它的执行几乎完全独立于父进程。当在进程中创建一个新线程时，新的执行线程将拥有自己的栈（因此也有自己的局部变量），但与它的创建者共享全局变量、文件描述符、信号处理函数和当前目录状态。

## 线程的优点和缺点

在某些环境下，创建新线程要比创建新进程有更明显的优势。新线程的创建代价要比新进程小得多。

下面是一些使用线程的优点：

- 让程序看起来好像是同时做两件事情。比如在编辑文档的同时对文档中的单词个数做实时统计。

- 一个混杂着输入、计算和输出的应用程序，可以将这几部分分离为3个线程来执行，从而改善程序的执行的性能。

- 一般而言，线程之间的切换需要操作系统做的工作要比进程之间的切换少得多，因此多个线程对资源的需求要远小于多个进程。

下面是线程的一些缺点：

- 编写多线程程序需要非常仔细的设计。在多线程程序中，因时序上的细微偏差或无意造成的变量共享而引发错误的可能性是很大的。

- 对多线程程序的调试要比对单线程程序的调试要困难得多，因为线程之间的交互非常难于控制。
 
- 将大量计算分成两个部分，并把这两个部分作为两个不同的线程来运行的程序在一台单处理器机器上并不一定运行得更快，除非计算确实允许它的不同部分可以被同时计算，而且运行它的机器拥有多个处理器核来支持真正的多处理。

## 第一个线程程序

线程库中的函数绝大多数都以pthread_开头，为了使用这些函数调用，我们必须定义宏_REENTRANT，在程序中包含头文件pthread.h，并且在编译程序时需要用选项-lpthread来链接线程库。

通过定义宏_REENTRANT来告诉编译器我们需要可重入功能，这个宏的定义必须位于程序中的任何#include语句之前。它将为我们做3件事情：

- 它会对部分函数重新定义它们的安全重入的版本，这些函数的名字一般不会发生改变，只是会在函数名后面添加_r字符串。

- stdio.h中原来以宏的形式实现的一些函数将变成可安全重入的函数。

- 在errno.h中定义的变量errno现在将称为一个函数调用，它能够以一种多线程安全的方式来获取真正的errno值。

创建线程的函数声明：

```c
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                  void *(*start_routine) (void *), void *arg);
```

第一个参数是线程标识符，当线程被创建时，它将被写入一个值，用来引用新线程。attr是线程的属性，可以设置为NULL保持默认。最后两个参数分别告诉线程将要启动执行的函数和传递给该函数的参数。

函数成功返回0，失败返回错误代码。

线程通过pthread_exit函数终止执行，就如同进程在结束时调用exit函数一样。这个函数的作用是，终止调用它的线程并返回一个指向某个对象的指针（这个对象不应该是一个局部变量）。

```c
#include <pthread.h>

void pthread_exit(void *retval);
```

pthread_join函数在线程中的作用等价于进程中用来收集子进程信息的wait函数。

```c
#include <pthread.h>

int pthread_join(pthread_t thread, void **retval);
```

第一个参数指定了将要等待的线程的标识符。第二个参数是一个指针，它指向另一个指针，后者指向线程的返回值。

[==案例代码==](https://github.com/demon90s/Beginning_Linux_Programming_CodeNote/blob/master/ch12_POSIX_thread/thread1.c)

编译多线程程序时，需要定义宏_REENTRNT，并链接多线程库。在我的机器上（CentOS7），编译的命令如：

```bash
$ gcc -D_REENTRANT -lpthread src.c -o out
```

新的线程将和原线程同时执行。

## 同步

有一组设计好的函数为我们提供了控制线程执行和访问代码临界区域的方法。

一种是信号量，它的作用如同看守一段代码的看门人。

另一种是互斥量，它的作用如同看守一段代码的互斥设备。

### 用信号量进行同步

信号量是一个特殊类型的变量，它可以被增加或减少，但对其的关键访问被保证是原子操作，即使在一个多线程程序中也是如此。这意味着如果一个程序中有两个（或更多）的线程试图改变一个信号量的值，系统将保证所有的操作都将依次进行。但如果是普通变量，来自同一个程序的不同线程的冲突操作所导致的结果将是不确定的。

本章节介绍的信号量是二进制信号量，它只有0或者1两种取值。二进制信号量能用于保护一段代码，使其每次只能被一个执行线程运行。

信号量通过sem_init函数创建，它的定义如下所示：

```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
```

这个函数初始化sem指向的信号量对象，pshared参数控制信号量的类型，如果值为0，就表示这个信号量是当前进程的局部信号量，否则，这个信号量就可以在多个进程之间共享。value是信号量的初始值。

接下来的两个函数控制信号量的值：

```c
#include <semaphore.h>

int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
```

sem_post的作用是以原子操作的方式给信号量的值加1。所谓原子操作是指，如果两个线程企图同时给一个信号量加1，它们之间不会互相干扰，信号量的值总是会被正确的地加2。

sem_wait函数以原子操作的方式将信号量的值减1。但它会等待直到信号量有个非零值才会开始减法操作。也就是说，如果对值为0的信号量调用sem_wait，这个函数就会等待，直到有其他线程增加了该信号量的值使其不再是0为止。

sem_destroy对用完的信号量进行清理：

```c
#include <semaphore.h>

int sem_destroy(sem_t *sem);
```

这些函数在成功时都返回0，并且会设置errno。

[==案例代码==](https://github.com/demon90s/Beginning_Linux_Programming_CodeNote/blob/master/ch12_POSIX_thread/thread3.c)

### 用互斥量进行同步

互斥量允许程序员锁住某个对象，使得每次只能有一个线程访问它。为了控制对关键代码的访问，必须在进入这段代码之前锁住一个互斥量，然后在完成操作之后解锁它。

```c
#include <pthread.h>

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

int pthread_mutex_destroy(pthread_mutex_t *mutex);

int pthread_mutex_lock(pthread_mutex_t *mutex);

int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

与其他函数一样，成功时返回0，失败时返回错误代码，但并不设置errno。attr允许我们设置互斥量的属性，它控制着互斥量的行为。

[==案例代码==](https://github.com/demon90s/Beginning_Linux_Programming_CodeNote/blob/master/ch12_POSIX_thread/thread4.c)

## 线程属性

之前的程序案例中，我们都在程序退出之前调用pthread_join对线程再次进行同步，如果我们想让线程向创建它的线程返回数据就需要这么做。但有时我们不需要第二个线程向主线程返回信息，也不想让主线程等待它的结束。

我们可以创建一种脱离线程（detached thread）。可以通过修改线程属性或调用pthread_detach的方法来创建它们。本节采用前一种方法。

pthread_attr_init可以初始化一个线程属性对象。

```c
#include <pthread.h>

int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
```

pthread_attr_destroy的目的是对属性对象进行清理和回收。函数成功时返回0，失败返回错误代码。

初始化一个线程属性对象后，我们可以调用许多其他的函数来设置不同的属性行为。书中主要介绍的是detachedstate和schedpolicy，见书本p431。 

## 取消一个线程

有时我们想让一个线程中止另一个线程的执行，就像给它发送一个信号一样。线程可以在被要求终止时改变其行为。

```c
#include <pthread.h>

int pthread_cancel(pthread_t thread);
```

线程可以用pthread_setcancelstate设置自己的取消状态。

```c
#include <pthread.h>

int pthread_setcancelstate(int state, int *oldstate);
int pthread_setcanceltype(int type, int *oldtype);
```

pthread_setcancelstate第一个参数的取值可以是PTHREAD_CANCEL_ENABLE，这个值允许线程接收取消请求；或者是PTHREAD_CANCEL_DISABLE，它的作用是忽略取消请求。oldstate指针用于获取先前的取消状态，如果对它没有兴趣，可以传递NULL给它。

pthread_setcanceltype的type有两种取值：一个是PTHREAD_CANCEL_ASYNCHRONOUS，它将使线程收到取消请求后立即采取行动；另一个是PTHREAD_CANCEL_DEFERRED，它将使得在接收到取消请求后，一直等待直到线程执行了某些函数后才采取行动，比如pthread_join。

默认情况下，线程在启动时的取消状态为PTHREAD_CANCEL_ENABLE, PTHREAD_CANCEL_DEFERRED。

[==案例代码==](https://github.com/demon90s/Beginning_Linux_Programming_CodeNote/blob/master/ch12_POSIX_thread/thread8.c)

书中在最后讨论了多线程的知识，一个进程可以创建许多线程并发执行。