/*
	#include <sys/sem.h>
	int semctl(int sem_id, int sem_num, int command, ...);

	semctl 用来直接控制信号量（由 sem_id 标示）的信息。
	sem_num 是信号量的编号，当需要用到成组的信号量时，会用到；一般取值为0 ，表示这是第一个也是唯一的一个信号量。
	command 是要采取的动作，可以有：
	- SETVAL 把信号量初始化为一个已知的值
	- IPC_RMID 删除一个信号量
	对于上面两个动作，成功返回0 ，失败返回 -1 。

	第四个参数竟然要程序员自己定义，可以定义成：
	union semun {
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	};

	如果 command 是 SETVAL ，那么 val 填写的就是初始值。
*/

#include <sys/sem.h>
#include <stdio.h>

#define KEY 1234

union semun {
	int val;
};

int main()
{
	int sem_id;
	sem_id = semget(KEY, 1, 0666 | IPC_CREAT);
	if (sem_id == -1) {
		fprintf(stderr, "semget failed\n");
		return 1;
	}

	// init sem
	{
		int res;
		union semun su;
		su.val = 1;
		res = semctl(sem_id, 0, SETVAL, su);

		if (res == 0)
			printf("semctl(SETVAL): init sem succ\n");
		else
			printf("semctl(SETVAL): init sem failed\n");
	}

	// delete sem
	{
		int res;
		res = semctl(sem_id, 0, IPC_RMID);
		
		if (res == 0)
			printf("semctl(IPC_RMID): delete sem succ\n");
		else
			printf("semctl(IPC_RMID): delete sem failed\n");
	}

	return 0;
}
