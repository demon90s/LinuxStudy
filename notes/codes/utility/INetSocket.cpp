#include "INetSocket.h"

#include <cstring>
#include <cstdio>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace utility
{
	static const unsigned short PORT = 12345;

	void Test_INetSocket_Server()
	{
		int socketfd = INetSocket::Socket();

		if (!INetSocket::Bind(socketfd, PORT)) {
			perror("Bind");
			return;
		}

		if (!INetSocket::Listen(socketfd)) {
			perror("Listen");
			return;
		}

		printf("[DEBUG] Server start.\n");

		while (true) {
			char ip[128] = {0};
			unsigned short port;
			int client_socketfd = INetSocket::Accept(socketfd, ip, &port);

			printf("[DEBUG] Accept a client from %s:%u\n", ip, port);

			// echo
			int nread = 0;
			do {
				static const int SIZE = 128;
				char buf[SIZE];
				nread = INetSocket::Recv(client_socketfd, buf, SIZE);

				if (nread > 0) {
					printf("[DEBUG] Recv message: %s\n", buf);
					INetSocket::Send(client_socketfd, buf, nread);
				}
				else if (nread == 0) {
					printf("[DEBUG] Connect closed\n");
					INetSocket::Close(client_socketfd);
				}
				
			} while (nread > 0);
		}

		INetSocket::Close(socketfd);
	}

	void Test_INetSocket_Client()
	{
		int socketfd = INetSocket::Socket();

		if (!INetSocket::Connect(socketfd, "127.0.0.1", PORT)) {
			perror("Connect");
			return;
		}

		printf("[DEBUG] Connect server.\n");

		int nread = 0;
		do {
			static const int SIZE = 128;
			char buf[SIZE];

			printf("Write some message: ");
			fgets(buf, SIZE, stdin);
			if (buf[strlen(buf) - 1] == '\n')
				buf[strlen(buf) - 1] = '\0';

			INetSocket::Send(socketfd, buf, strlen(buf) + 1);
			nread = INetSocket::Recv(socketfd, buf, SIZE);
			if (nread > 0) {
				printf("[DEBUG] Recv message: %s\n", buf);
			}

		} while (nread > 0);

		INetSocket::Close(socketfd);
	}
}

namespace utility
{

int INetSocket::Socket()
{
	return socket(AF_INET, SOCK_STREAM, 0);
}

bool INetSocket::Bind(int socketfd, unsigned short port)
{
	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	return bind(socketfd, (struct sockaddr*)&address, sizeof(address)) == 0;
}

bool INetSocket::Listen(int socketfd, int backlog)
{
	return listen(socketfd, backlog) == 0;
}

int INetSocket::Accept(int socketfd, char* ip_out, unsigned short *port_out)
{
	struct sockaddr_in address;
	socklen_t address_len;
	int new_socketfd = accept(socketfd, (struct sockaddr*)&address, &address_len);

	if (new_socketfd != -1)
	{
		if (ip_out) {
			const char* ip = inet_ntoa(address.sin_addr);
			strcpy(ip_out, ip);
		}
		if (port_out)
			*port_out = ntohs(address.sin_port);
	}

	return new_socketfd;
}

bool INetSocket::Close(int socketfd)
{
	return close(socketfd) == 0;
}

bool INetSocket::Connect(int socketfd, const char *ip, unsigned short port)
{
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip);
	address.sin_port = htons(port);

	return connect(socketfd, (struct sockaddr*)&address, sizeof(address)) == 0;
}

int INetSocket::Send(int socketfd, const void* buf, int size)
{
	return write(socketfd, buf, size);
}

int INetSocket::Recv(int socketfd, void *buf, int size)
{
	return read(socketfd, buf, size);
}

}
