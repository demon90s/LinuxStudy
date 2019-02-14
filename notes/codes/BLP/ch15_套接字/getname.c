#include <stdlib.h>
#include <stdio.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
	char *host, **names, **addrs;
	struct hostent *hostinfo;

	// 把host变量设置为用户主机的主机名，或者参数1指定的主机名
	if (1 == argc) {
		char myname[256] = {0};
		gethostname(myname, 255);
		host = myname;
	} else {
		host = argv[1];
	}

	// 调用gethostbyname，如果未找到相应的信息就报告一条错误
	hostinfo = gethostbyname(host);
	if (!hostinfo) {
		fprintf(stderr, "cannot get info for host: %s\n", host);
		exit(EXIT_FAILURE);
	}

	// 显示主机名和它可能有的所有别名
	printf("results for host: %s\n", host);
	printf("Name: %s\n", hostinfo->h_name);
	printf("Aliases:");
	names = hostinfo->h_aliases;
	while (*names) {
		printf(" %s", *names);
		names++;
	}
	printf("\n");

	// 如果查询的主机不是一个IP主机，就发出警告并退出
	if (hostinfo->h_addrtype != AF_INET) {
		fprintf(stderr, "not an IP host\n");
		exit(EXIT_FAILURE);
	}

	// 否则，显示它所有的IP地址：
	addrs = hostinfo->h_addr_list;
	while (*addrs) {
		printf(" %s", inet_ntoa(*(struct in_addr*)*addrs));
		addrs++;
	}
	printf("\n");

	exit(EXIT_SUCCESS);
}
