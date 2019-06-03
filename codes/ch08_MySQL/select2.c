// 实验：提取数据并打印
//
// 简单的提取数据的例程，打印出提取出的每一行的内容

#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

#define TRUE 1
#define FALSE 0

typedef int BOOL;

static MYSQL my_connection;

void PrintFailedInfo(const char *prefix);
BOOL Connect();
BOOL Query();
BOOL FetchRes();
void display_row(const MYSQL_ROW sqlrow);	// 打印一行的内容

int main()
{
	mysql_init(&my_connection);

	if (Connect() && Query()) {
		FetchRes();
	}

	mysql_close(&my_connection);

	return 0;
}

void PrintFailedInfo(const char *prefix)
{
	int error_num;

	error_num = mysql_errno(&my_connection);
	if (error_num) {
		fprintf(stderr, "%s %d: %s\n", prefix, error_num, mysql_error(&my_connection));
	}
}

BOOL Connect()
{
	const char *sock_name = "/data/mysql.sock"; // or NULL
	if (NULL == mysql_real_connect(&my_connection, "localhost", "rick", "secret", "foo", 0, sock_name, 0)) {
		PrintFailedInfo(__FUNCTION__);
		return FALSE;
	}

	return TRUE;
}

BOOL Query()
{
	int ret;

	ret = mysql_query(&my_connection, "SELECT childno, fname, age FROM children WHERE age > 2");
	if (0 != ret) {
		PrintFailedInfo(__FUNCTION__);
		return FALSE;
	}

	return TRUE;
}

BOOL FetchRes()
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;

	res_ptr = mysql_store_result(&my_connection);
	//res_ptr = mysql_use_result(&my_connection);	// 这种情况下，使用mysql_num_rows没有意义，会返回0
	if (res_ptr) {
		printf("Retrieved %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow = mysql_fetch_row(res_ptr))) {
			printf("Fetched data...\n");
			display_row(sqlrow);
		}

		mysql_free_result(res_ptr);
		return TRUE;
	} else {
		PrintFailedInfo(__FUNCTION__);
		return FALSE;
	}
}

void display_row(const MYSQL_ROW sqlrow)
{
	int i;
	unsigned int total_field_count;

	total_field_count = mysql_field_count(&my_connection);
	for (i = 0; i < total_field_count; ++i) {
		printf("%s ", sqlrow[i]);
	}
	printf("\n");
}

