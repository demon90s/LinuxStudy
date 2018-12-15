/*
 * #include <ndbm.h>
 *
 * datum dbm_firstkey(DBM *database_descriptor);
 * datum dbm_nextkey(DBM *database_descriptor);
 *
 * dbm_firstkey 获取数据库中第一个 key ，dbm_nextkey 获取数据库中下一个 key 。
 * 用于对数据库进行扫描。
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

int main(int argc, char *argv[])
{
	DBM *database_descriptor;
	datum key, content;

 	database_descriptor = dbm_open("testdb", O_RDWR | O_CREAT, 0666);
	if (database_descriptor == NULL) {
		fprintf(stderr, "dbm_open failed\n");
		exit(EXIT_FAILURE);
	}

	/* 先插入若干条数据 */
	{
		const char* store_strs[5] = {
			"Hello", "World", "Linux", "DBM", "Lab"
		};

		int key_id;
		for (key_id = 0; key_id <  5; ++key_id) {
			key.dptr = (void*)&key_id;
			key.dsize = sizeof(key_id);

			content.dptr = (void*)store_strs[key_id];
			content.dsize = strlen(store_strs[key_id]);

			dbm_store(database_descriptor, key, content, DBM_REPLACE);
		}
	}

	/* 遍历这些数据 */
	{
		char *content_str;
		int key_id;

		key = dbm_firstkey(database_descriptor);
		for (; key.dptr; key = dbm_nextkey(database_descriptor)) {
			content = dbm_fetch(database_descriptor, key);
			if (content.dptr != NULL) {
				content_str = malloc(content.dsize + 1);
				assert(content_str != NULL);
				memcpy(&key_id, key.dptr, key.dsize);

				strcpy(content_str, content.dptr);
				printf("get data(key:value) - %d:%s\n", key_id, content_str);

				free(content_str);
			}
		}
	}

	dbm_close(database_descriptor);

	return 0;
}
