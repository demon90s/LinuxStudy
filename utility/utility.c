#include "utility.h"

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int copy_file(const char *src_file, const char *dest_file)
{
	char block[1024];
	int in, out;
	int nread;

	in = open(src_file, O_RDONLY);
	if (-1 == in) {
		perror("copy_file failed");
		return 1;
	}

	out = open(dest_file, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	while ((nread = read(in, block, sizeof(block) > 0)))
		write(out, block, nread);

	return 0;
}
