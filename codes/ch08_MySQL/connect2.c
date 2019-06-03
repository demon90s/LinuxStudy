// 实验：连接数据库并处理错误
//
// 简单的连接数据库foo的例程，出错后使用相关接口打印错误信息

#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main()
{
	int error_num;
	MYSQL my_connection;
	mysql_init(&my_connection);

	const char *sock_name = NULL; // or "/data/mysql.sock"
	if (mysql_real_connect(&my_connection, "localhost", "rick", "secret", "foo", 0, sock_name, 0)) {
		printf("Connection success\n");
	} else {
		error_num = mysql_errno(&my_connection);
		if (error_num) {
			fprintf(stderr, "Connection error %d: %s\n", error_num, mysql_error(&my_connection));
		}
	}

	mysql_close(&my_connection);

	return 0;
}
