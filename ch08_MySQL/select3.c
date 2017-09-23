// 简单的提取数据的例程，打印出提取出的每一行的内容，并且打印出列的详细信息

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
void display_header(MYSQL_RES *res_ptr);	// 打印出列的详细信息
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
	if (res_ptr) {
		display_header(res_ptr);
		printf("Retrieved %lu rows:\n", (unsigned long)mysql_num_rows(res_ptr));
		while ((sqlrow = mysql_fetch_row(res_ptr))) {
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

void display_header(MYSQL_RES *res_ptr)
{
	MYSQL_FIELD *field_ptr;

	printf("Column details:\n");
	while ((field_ptr = mysql_fetch_field(res_ptr)) != NULL) {
		printf("\t Name: %s\n", field_ptr->name);
		printf("\t Type: ");
		
		if (IS_NUM(field_ptr->type)) printf("Numberic\n");
		else if (field_ptr->type == FIELD_TYPE_VAR_STRING) printf("VARCHAR\n");
		else printf("%d, check in mysql_com.h\n", field_ptr->type);

		if (field_ptr->flags & AUTO_INCREMENT_FLAG)
			printf("\t Auto increments\n");
		
		printf("\n");
	}
}

