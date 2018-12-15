#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
do { perror(msg); exit(EXIT_FAILURE); } while(0)

int main()
{
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct sockaddr_in server_address, client_address;

	// Remove any old sockets and create an unnamed socket for the server
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// Name the socket
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	if (-1 == bind(server_sockfd, (struct sockaddr*)&server_address, server_len)) {
		handle_error("bind");
	}

	// Create a connection queue and wait for client
	listen(server_sockfd, 5);

	// 忽略子进程的退出细节
	signal(SIGCHLD, SIG_IGN);

	while (1) {
		char ch;
		printf("server waiting\n");

		// Accept a connection
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);

		// 通过fork调用为这个客户创建一个子进程，然后测试你在父进程中还是子进程中
		if (fork() == 0) {

			// 如果是在子进程中，就可以对client_sockfd上的客户执行读写操作。5秒的延迟出于演示目的
			read(client_sockfd, &ch, 1);
			sleep(5);	// 模拟服务计算
			ch++;
			write(client_sockfd, &ch, 1);
			close(client_sockfd);
			exit(0);
		} else {
			// 否则，一定在父进程中，只需关闭这个客户
			close(client_sockfd);
		}
	}

	exit(0);
}

