#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct sockaddr_in server_address, client_address;
	int result;
	fd_set readfds, testfds;

	// 为服务器创建并命名一个套接字
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr*)&server_address, server_len);

	// 创建一个连接队列，初始化readfds以处理来自server_sockfd的输入
	listen(server_sockfd, 5);

	FD_ZERO(&readfds);
	FD_SET(server_sockfd, &readfds);

	// 等待客户和请求的到来，select将阻塞调用，如果返回值小于1，程序退出并报告错误
	while (1) {
		char ch;
		int fd;
		int nread;

		testfds = readfds;

		printf("server waiting\n");

		result = select(FD_SETSIZE, &testfds, NULL, NULL, NULL);
		if (result < 1) {
			perror("server");
			exit(1);
		}

		// select成功返回说明有活动发生，使用FD_ISSET检查每个描述符，以发现活动发生在哪个描述符上
		for (fd = 0; fd < FD_SETSIZE; fd++) {
			if (FD_ISSET(fd, &testfds)) {
				// 如果发生在server_sockfd，它肯定是一个新的连接请求，把新的client_sockfd添加到readfds
				if (fd == server_sockfd) {
					client_len = sizeof(client_address);
					client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
					FD_SET(client_sockfd, &readfds);
					printf("[DEBUG] adding client on fd %d\n", client_sockfd);
				} else {
					// 否则肯定是客户的活动。如果收到的活动是close，就说明客户已经断开，就把它关联的套接字从描述符集合中删除。否则为客户服务
					ioctl(fd, FIONREAD, &nread);
					if (nread == 0) {
						close(fd);
						FD_CLR(fd, &readfds);
						printf("[DEBUG] removing client on fd %d\n", fd);
					} else {
						read(fd, &ch, 1);
						printf("[DEBUG] serving client on fd %d\n", fd);
						sleep(5);
						ch++;
						write(fd, &ch, 1);
					}
				}
			}
		}
	}

	exit(0);
}

