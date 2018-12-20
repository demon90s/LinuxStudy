/*
 * #include <ndbm.h>
 *
 * DBM *dbm_open(const char *filename, int file_open_flag, mode_t file_mode);
 * void dbm_close(DBM *database_descriptor);
 *
 * dbm_open 打开一个已有的数据库，或者创建新的数据库，其名字为 filename ，对应的文件是 filename.dir 和
 * filename.pag
 * file_open_flag 和 file_mode 的取值与 open 函数一致。
 * 函数失败返回空指针。
 *
 * dbm_close 关闭掉由 dbm_open 打开的数据库。
 */

#include <ndbm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	DBM *database_descriptor;

 	database_descriptor = dbm_open("testdb", O_RDWR | O_CREAT, 0666);
	if (database_descriptor == NULL) {
		fprintf(stderr, "dbm_open failed\n");
		exit(EXIT_FAILURE);
	}
	printf("dbm_open\n");

	/* do your work  */

	dbm_close(database_descriptor);
	printf("dbm_close\n");

	return 0;
}
