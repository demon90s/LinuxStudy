// 实验：使用mysql_query插入记录
//
// 简单的执行插入SQL语句的例程

#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

#define TRUE 1
#define FALSE 0

typedef int BOOL;

static MYSQL my_connection;

BOOL Connect();
BOOL Query();

int main()
{
	mysql_init(&my_connection);

	if (Connect()) {
		Query();
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

