all: epoll_server epoll_client

CC=g++

epoll_server: epoll_server.o

epoll_client: epoll_client.o

epoll_server.o: epoll_server.cpp

epoll_client.o: epoll_client.cpp

clean:
	rm *.o epoll_server epoll_client