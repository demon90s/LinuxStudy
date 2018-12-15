#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

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
	bind(server_sockfd, (struct sockaddr*)&server_address, server_len);

	// Create a connection queue and wait for client
	listen(server_sockfd, 5);
	while (1) {
		char ch;
		printf("server waiting\n");

		// Accept a connection
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);

		// Read and write to client on client_sockfd
		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
	}

	exit(0);
}

