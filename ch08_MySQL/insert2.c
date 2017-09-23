// 简单的执行插入SQL语句的例程，并打印出最后一次插入的ID

#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

#define TRUE 1
#define FALSE 0

typedef int BOOL;

static MYSQL my_connection;

BOOL Connect();
BOOL Query();
BOOL PrintLastInsertID();

int main()
{
	mysql_init(&my_connection);

	if (Connect() && Query()) {
		PrintLastInsertID();
	}

	mysql_close(&my_connection);

	return 0;
}

BOOL Connect()
{
	int error_num;

	const char *sock_name = "/data/mysql.sock"; // or NULL
	if (NULL == mysql_real_connect(&my_connection, "localhost", "rick", "secret", "foo", 0, sock_name, 0)) {
		error_num = mysql_errno(&my_connection);
		if (error_num) {
			fprintf(stderr, "Connect error %d: %s\n", error_num, mysql_error(&my_connection));
		}
		
		return FALSE;
	}

	return TRUE;
}

BOOL Query()
{
	int ret;

	ret = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('Ann', 3)");
	//ret = mysql_query(&my_connection, "DELETE FROM children");
	if (0 == ret) {
		printf("Inserted %lu rows\n", (unsigned long)mysql_affected_rows(&my_connection));
		return TRUE;
	} else {
		fprintf(stderr, "Insert error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
		return FALSE;
	}
}

BOOL PrintLastInsertID()
{
	int res;
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;

	res = mysql_query(&my_connection, "SELECT LAST_INSERT_ID()");
	if (0 != res) {
		printf("SELECT error: %s\n", mysql_error(&my_connection));
		return FALSE;
	} else {
		res_ptr = mysql_use_result(&my_connection);
		if (res_ptr) {
			while ((sqlrow = mysql_fetch_row(res_ptr))) {
				printf("Inserted childno: %s\n", sqlrow[0]);
			}
			mysql_free_result(res_ptr);
		}
	}

	return TRUE;
}

