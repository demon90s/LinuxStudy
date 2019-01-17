/*
	#include <netdb.h>

	struct hostent *gethostbyname(const char *name);

	根据主机名返回主机数据库
	struct hostent 至少包含：

	struct hostent {
		char *h_name;		// name of the host
		char **h_aliases;	// list of aliase (nicknames)
		int h_addrtype;		// address type
		int h_length;		// length in bytes of the address
		char **h_addr_list;	// list of address(network order)
	};

	失败返回空指针。

	Note:
	由于获得的地址是网络字节序，所以要用 inet_ntoa 将网络字节序转换为可打印的字符串。

*/

#include <unistd.h>
#include <arpa/inet.h>	// for inet_ntoa
#include <netdb.h>
#include <assert.h>
#include <stdio.h>

int main()
{
	char hostname[255];
	gethostname(hostname, sizeof(hostname));

	struct hostent *he = gethostbyname(hostname);
	if (he == NULL) {
		fprintf(stderr, "gethostbyname failed\n");
		return 1;
	}

	// print host data
	printf("host ent is:\n");
	printf("------------\n");
	
	printf("name of the host: %s\n", he->h_name);
	
	printf("list of aliase:");
	{
		char **name = he->h_aliases;
		while (*name) {
			printf(" [%s]", *name);
			name++;
		}
		printf("\n");
	}
	
	printf("address type is AF_INET? %s\n", he->h_addrtype == AF_INET ? "yes" : "no");
	assert(he->h_addrtype == AF_INET); // 下面强制转换依赖于此

	printf("list of ip:");
	{
		char **addr = he->h_addr_list;
		while (*addr) {
			printf(" [%s]", inet_ntoa(*(struct in_addr*)*addr));
			addr++;
		}
		printf("\n");
	}

	return 0;
}
