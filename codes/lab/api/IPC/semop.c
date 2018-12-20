/*
	#include <sys/sem.h>
	int semop(int sem_id, struct sembuf *sem_ops, size_t num_sem_ops);

	用于改变信号量（由 sem_id 标示）的值。
	如果就一个信号量，num_sem_ops 为1 。
	sem_ops 是改变的内容，它至少有：
	struct sembuf {
		short sem_num;	// 信号量编号，如果只有一个，取0
		short sem_op;	// 信号量改变的值，通常是-1（P操作）或1（V操作）
		short sem_flg;	// 通常为 SEM_UNDO ，它将使操作系统跟踪当前进程对这个信号量的修改情况，如果这个进程在没有释放该信号量的情况下终止，操作系统将自动释放该进程持有的信号量。
	};

	函数失败返回 -1 。
*/

#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define KEY 1234

union semun {
	int val;
};

static int sem_id;

void PV(char test_char) {
	int loop = 0;
	while (loop++ < 5) {
		struct sembuf sb;
		sb.sem_num = 0;
		sb.sem_op = test_char == 'P' ? -1 : 1;
		sb.sem_flg = SEM_UNDO;
		if (semop(sem_id, &sb, 1) == -1) {
			fprintf(stderr, "semop P failed\n");
			return;
		}
		printf("semop P succ, lock critical code section, pid(%d)\n", getpid());

		{
			FILE *fp = fopen("/tmp/test_semop.txt", "a");
			if (fp) {
				fprintf(fp, "%c", test_char); // 锁定了代码区，打印字符一定成对出现
				sleep(1);
				fprintf(fp, "%c", test_char);
				fclose(fp);
			}
		}

		sb.sem_op = test_char == 'P' ? 1 : -1;
		if (semop(sem_id, &sb, 1) == -1) {
			fprintf(stderr, "semop V failed\n");
			return;
		}
		printf("semop V succ, unlock critical code section, pid(%d)\n", getpid());
	}
}

int main(int argc, char *argv[])
{
	int sem_flags = 0666;
	char test_char = 'V';

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <p|v>\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "p") == 0) {
		sem_flags |= IPC_CREAT;
		test_char = 'P';
	}

	sem_id = semget(KEY, 1, sem_flags);
	if (sem_id == -1) {
		fprintf(stderr, "semget failed\n");
		return 1;
	}

	// init
	if (test_char == 'P') {
		union semun su;
		su.val = 0;
		if (semctl(sem_id, 0, SETVAL, su) != 0) {
			fprintf(stderr, "init semaphore failed\n");
			return 1;
		}
	}

	PV(test_char);

	// delete
	if (test_char == 'P') {
		if (semctl(sem_id, 0, IPC_RMID) != 0) {
			fprintf(stderr, "delete semaphore failed\n");
		}
	}
	return 0;
}
