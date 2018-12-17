// 实验：通过管道读取大量数据

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SZ 1024

int main()
{
	FILE *read_fp;
	char buffer[BUFFER_SZ + 1];
	int chars_read;

	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen("ps ax", "r");
	if (read_fp != NULL) {
		chars_read = fread(buffer, sizeof(char), BUFFER_SZ, read_fp);
		while (chars_read > 0) {
			buffer[chars_read - 1] = '\0';
			printf("Reading %d:-\n%s\n", chars_read, buffer);
			chars_read = fread(buffer, sizeof(char), BUFFER_SZ, read_fp);
		}

		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}
