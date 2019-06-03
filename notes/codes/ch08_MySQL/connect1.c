// 实验：连接数据库
//
// 简单的连接数据库foo的例程

/*
 MYSQL *mysql_real_connect(MYSQL *connection, )
							const char *server_host,
							const char *sql_user_name,
							const char *sql_password,
							const char *db_name,
							unsigned int port_number,
							const cahr *unix_socket_name,
							unsigned int flags);
*/

#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main()
{
	MYSQL *conn_ptr;
	conn_ptr = mysql_init(NULL);

	if (!conn_ptr) {
		fprintf(stderr, "mysql_init failed\n");
		return EXIT_FAILURE;
	}

	const char *sock_name = "/data/mysql.sock"; // or NULL
	conn_ptr = mysql_real_connect(conn_ptr, "localhost", "rick", "secret", "foo", 0, sock_name, 0);
	if (conn_ptr) {
		printf("Connection success\n");
	} else {
		printf("Connection failed\n");
	}

	mysql_close(conn_ptr);

	return 0;
}

