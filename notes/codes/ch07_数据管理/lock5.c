// 实验：文件锁的竞争

// 先运行 ./lock3 ，然后运行 ./lock5 观测

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

const char *test_file = "/tmp/test_lock";

int main()
{
	int file_desc;
	struct flock region_to_lock;
	int res;

	file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
	if (file_desc == -1) {
		fprintf(stderr, "Unable to open %s for read/write\n", test_file);
		exit(EXIT_FAILURE);
	}

	// 指定文件的不同区域，并尝试在它们之上执行不同的锁定操作
	region_to_lock.l_type = F_RDLCK;
	region_to_lock.l_whence = SEEK_SET;
	region_to_lock.l_start = 10;
	region_to_lock.l_len = 5;
	printf("Process %d, trying F_RDLCK, region %d to %d\n", getpid(),
			(int)region_to_lock.l_start, (int)(region_to_lock.l_start + region_to_lock.l_len));

	res = fcntl(file_desc, F_SETLK, &region_to_lock);
	if (res == -1) {
		printf("Process %d - failed to lock region\n", getpid());
	}
	else {
		printf("Process %d - obtained lock region\n", getpid());
	}

	region_to_lock.l_type = F_UNLCK;
	region_to_lock.l_whence = SEEK_SET;
	region_to_lock.l_start = 10;
	region_to_lock.l_len = 5;
	printf("Process %d, trying F_UNLCK, region %d to %d\n", getpid(), (int)region_to_lock.l_start,
			(int)(region_to_lock.l_start + region_to_lock.l_len));
	res = fcntl(file_desc, F_SETLK, &region_to_lock);
	if (res == -1) {
		printf("Process %d - failed to unlock region\n", getpid());
	}
	else {
		printf("Process %d - unlocked region\n", getpid());
	}

	region_to_lock.l_type = F_UNLCK;
	region_to_lock.l_whence = SEEK_SET;
	region_to_lock.l_start = 0;
	region_to_lock.l_len = 50;
	printf("Process %d, trying F_UNLCK, region %d to %d\n", getpid(),
			(int)(region_to_lock.l_start), (int)(region_to_lock.l_start + region_to_lock.l_len));
	res = fcntl(file_desc, F_SETLK, &region_to_lock);
	if (res == -1) {
		printf("Process %d - failed to unlock region\n", getpid());
	}
	else {
		printf("Process %d - unlocked region\n", getpid());
	}

	region_to_lock.l_type = F_WRLCK;
	region_to_lock.l_whence = SEEK_SET;
	region_to_lock.l_start = 16;
	region_to_lock.l_len = 5;
	printf("Process %d, trying F_WRLCK, region %d to %d\n", getpid(),
			(int)(region_to_lock.l_start), (int)(region_to_lock.l_start + region_to_lock.l_len));
	res = fcntl(file_desc, F_SETLK, &region_to_lock);
	if (res == -1) {
		printf("Process %d - failed to lock region\n", getpid());
	}
	else {
		printf("Process %d - obtained lock on region\n", getpid());
	}

	region_to_lock.l_type = F_RDLCK;
	region_to_lock.l_whence = SEEK_SET;
	region_to_lock.l_start = 40;
	region_to_lock.l_len = 10;
	printf("Process %d, trying F_RDLCK, region %d to %d\n", getpid(),
			(int)(region_to_lock.l_start), (int)(region_to_lock.l_start + region_to_lock.l_len));
	res = fcntl(file_desc, F_SETLK, &region_to_lock);
	if (res == -1) {
		printf("Process %d - failed to lock region\n", getpid());
	}
	else {
		printf("Process %d - obtained lock on region\n", getpid());
	}

	region_to_lock.l_type = F_WRLCK;
	region_to_lock.l_whence = SEEK_SET;
	region_to_lock.l_start = 16;
	region_to_lock.l_len = 5;
	printf("Process %d, trying F_WRLCK, region %d to %d\n", getpid(),
			(int)(region_to_lock.l_start), (int)(region_to_lock.l_start + region_to_lock.l_len));
	res = fcntl(file_desc, F_SETLKW, &region_to_lock);
	if (res == -1) {
		printf("Process %d - failed to lock region\n", getpid());
	}
	else {
		printf("Process %d - obtained lock on region\n", getpid());
	}

	printf("Process %d ending\n", getpid());

	close(file_desc);

	exit(EXIT_SUCCESS);
}
