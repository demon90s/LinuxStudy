#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	char *host;
	int sockfd;
	int result;
	socklen_t len;
	struct sockaddr_in address;
	struct hostent *hostinfo;
	struct servent *servinfo;
	char buffer[128];

	if (1 == argc) {
		host = "localhost";
	} else {
		host = argv[1];
	}

	// 查找主机的地址，如果找不到，就报告一条错误
	hostinfo = gethostbyname(host);
	if (!hostinfo) {
		fprintf(stderr, "no host: %s\n", host);
		exit(EXIT_FAILURE);
	}

	// 检查主机上是否有daytime服务
	servinfo = getservbyname("daytime", "tcp");
	if (!servinfo) {
		fprintf(stderr, "no daytime service\n");
		exit(EXIT_FAILURE);
	}
	printf("daytime port is %d\n", ntohs(servinfo->s_port));

	// 创建一个UDP套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// Construct the address for use with sendto/recvfrom...
	address.sin_family = AF_INET;
	address.sin_port = servinfo->s_port;
	address.sin_addr = *(struct in_addr*)*hostinfo->h_addr_list;
	len = sizeof(address);

	result = sendto(sockfd, buffer, 1, 0, (struct sockaddr*)&address, len);
	result = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&address, &len);

	buffer[result] = '\0';
	printf("read %d bytes: %s", result, buffer);

	close(sockfd);

	exit(EXIT_SUCCESS);
}
