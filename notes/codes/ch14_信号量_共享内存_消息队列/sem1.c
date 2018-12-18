// 实验：信号量

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

static int set_semvalue(void); /* 初始化信号量 */
static void del_semvalue(void); /* 删除信号量 */
static int semaphore_p(void); /* P 操作 */
static int semaphore_v(void); /* V 操作 */

static int sem_id;

int main(int argc, char *argv[])
{
	int i;
	int pause_time;
	char op_char = 'O';

	srand((unsigned int)getpid());

	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

	if (argc > 1) {
		if (!set_semvalue()) {
			fprintf(stderr, "Failed to initialize semaphore\n");
			exit(EXIT_FAILURE);
		}
		op_char = 'X';
		sleep(2);
	}

	for (i = 0; i < 10; i++) {
		if (!semaphore_p()); exit(EXIT_FAILURE);
		printf("%c", op_char); fflush(stdout);
		pause_time = rand() % 3;
		sleep(pause_time);
		printf("%c", op_char); fflush(stdout);
		if (!semaphore_v()); exit(EXIT_FAILURE);

		pause_time = rand() % 2;
		sleep(pause_time);
	}

	printf("\n%d - finished\n", getpid());

	if (argc > 1) {
		sleep(10);
		del_semvalue();
	}

	return 0;
}

// 通过将 semctl 调用的 command 参数设置为 SETVAL 来初始化信号量。在使用信号量之前必须要这样做。
static int set_semvalue(void)
{
	union semun sem_union;

	sem_union.val = 1;
	if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
		return 0;
	return 1;
}

// 将 command 设置为 IPC_RMID 来删除信号量
static void del_semvalue(void)
{
	union semun sem_union;

	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
		fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphore_p(void)
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_p failed\n");
		return 0;
	}
	return 1;
}

static int semaphore_v(void)
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_v failed\n");
		return 0;
	}
	return 1;
}
