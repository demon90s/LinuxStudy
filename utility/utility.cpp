#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "utility.h"

namespace utility
{

void ParseParam(const char *str, std::vector<std::string> &result, const char *delim)
{
	char *temp = (char*)malloc(strlen(str) + 1);
	
	strncpy(temp, str, strlen(str) + 1);
	result.clear();

	char *token = strtok(temp, delim);
	while (token)
	{
		result.push_back(token);
		token = strtok(NULL, delim);
	}

	free(temp);
}

bool CopyFile(const char *src_file, const char *dest_file)
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

void Execute(const char *cmd)
{
	char *cmd_list[64] = {0};
	std::vector<std::string> cmd_list_tmp;
	
	ParseParam(cmd, cmd_list_tmp, " ");
	if (cmd_list_tmp.size() <= 0 || cmd_list_tmp.size() + 1 >= sizeof(cmd_list))
	{
		fprintf(stderr, "Execute: invalid argument\n");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < cmd_list_tmp.size(); ++i)
	{
		cmd_list[i] = (char*)cmd_list_tmp[i].c_str();
	}

	if (-1 == execvp(cmd_list[0], cmd_list))
	{
		perror("Execute error");
		exit(EXIT_FAILURE);
	}
}

}
