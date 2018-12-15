/*
 * #include <ndbm.h>
 *
 * int dbm_store(DBM *database_descriptor, datum key, datum content, int store_mode);
 * datum dbm_fetch(DBM *database_descriptor, datum key);
 * int dbm_delete(DBM *database_descriptor, datum key);
 *
 * datum 结构包含两个成员：
 * - dptr, 指向具体数据空间
 * - dsize, 数据的大小
 *
 * dbm_store 想数据库中存储一条记录，键是 key , 值是 content ，store_mode 可以是：
 * - DBM_INSERT 如果数据库中没有 key 记录，则插入
 * - DBM_REPLACE ，无论有没有 key 记录，都将记录插入/覆盖
 *
 * 函数返回0代表成功，如果 store_mode 返回1代表数据库中已经有一条记录了，其余情况返回复数代表失败
 *
 * dbm_fetch 用于从数据库中抓取 key 相应的数据。如果 datum.dptr 为空指针，表示没有找到。
 * 抓取后，需要把数据拷贝到另一个存储空间中去(比如使用 memcpy )。
 *
 * dbm_delete 从数据库中删除 key 相应的数据。成功返回0 。
 * 
 */

#include <ndbm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char *usage = "Usage: ./store_fetch <store|fetch|delete>";

int main(int argc, char *argv[])
{
	DBM *database_descriptor;
	const char* cmd;
	datum key, content;

	if (argc != 2) {
		printf("%s\n", usage);
		exit(EXIT_FAILURE);
	}

 	database_descriptor = dbm_open("testdb", O_RDWR | O_CREAT, 0666);
	if (database_descriptor == NULL) {
		fprintf(stderr, "dbm_open failed\n");
		exit(EXIT_FAILURE);
	}

	cmd = argv[1];

	/* do your work  */
	if (strcmp(cmd, "store") == 0) {
		int key_id = 100;
		key.dptr = (void*)&key_id;
		key.dsize = sizeof(key_id);

		const char* content_str = "This this a secret data￥%&*!@";
		content.dptr = (void*)content_str;
		content.dsize = strlen(content_str);
		int res = dbm_store(database_descriptor, key, content, DBM_REPLACE);	
		if (res != 0) {
			fprintf(stderr, "Ouch - dbm_store failed on key %d\n", key_id);
		}
		else {
			printf("dbm_store succ on key %d\n", key_id);
		}
	}
	else if (strcmp(cmd, "fetch") == 0) {
		int key_id = 100;
		key.dptr = (void*)&key_id;
		key.dsize = sizeof(key_id);
		
		content = dbm_fetch(database_descriptor, key);
		if (content.dptr == NULL) {
			fprintf(stderr, "Ouch - dbm_fetch failed on key %d\n", key_id);
		}
		else {
			char *content_str = malloc(content.dsize + 1);
			assert(content_str != NULL);

			strcpy(content_str, content.dptr);
			printf("dbm_fetch succ on key %d: %s\n", key_id, content_str);

			free(content_str);
		}
	}
	else if (strcmp(cmd, "delete") ==  0) {
		int key_id = 100;
		key.dptr = (void*)&key_id;
		key.dsize = sizeof(key_id);
		
		int res = dbm_delete(database_descriptor, key);
		if (res == 0) {
			printf("dbm_delete succ on key %d\n", key_id);
		}
		else {
			fprintf(stderr, "dbm_delete failed on key %d\n", key_id);
		}
	}

	dbm_close(database_descriptor);

	return 0;
}
