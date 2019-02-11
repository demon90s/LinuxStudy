#include "Network.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "HeartBeat.h"

namespace utility
{

static const int MAX_CONNECT_COUNT = 512;
static_assert(MAX_CONNECT_COUNT < FD_SETSIZE, "MAX_CONNECT_COUNT LIMIT");

Network::Network(std::shared_ptr<INetworkCallback> callback) : m_server_sockfd(-1), m_callback(callback)
{
	FD_ZERO(&m_readfds_from_client);
	FD_ZERO(&m_readfds_from_server);
	memset(m_buffer, 0, sizeof(m_buffer));
}

Network::~Network()
{
	close(m_server_sockfd);
	for (auto &connect_item : m_connect_item_list)
	{
		this->Disconnect(connect_item.netid);
	}
}

Network::ConnectItem* Network::GetConnectItem(NetID netid)
{
	if (netid < 0 || netid >= (int)m_connect_item_list.size())
	{
		return nullptr;
	}

	const auto &connect_item = m_connect_item_list[netid];
	if (!connect_item.valid)
	{
		return nullptr;
	}

	return &m_connect_item_list[netid];
}

void Network::CheckRecvFromClient()
{
	struct sockaddr_in client_address;
	socklen_t client_len;
	struct timeval timeout = {0, 1};

	fd_set testfds = m_readfds_from_client;
	int result = select(FD_SETSIZE, &testfds, NULL, NULL, &timeout);	
	if (result == -1)
	{
		perror("Network::CheckRecvFromClient select");
		return;
	}

	if (result < 1) return;

	// select成功返回说明有活动发生，使用FD_ISSET检查每个描述符，以发现活动发生在哪个描述符上
	for (int fd = 0; fd < FD_SETSIZE; fd++) {
	    if (!FD_ISSET(fd, &testfds)) continue;

		// 如果发生在server_sockfd，它肯定是一个新的连接请求，把新的client_sockfd添加到readfds
		if (fd == m_server_sockfd) {
			if ((int)m_sockfd_to_netid_map.size() >= MAX_CONNECT_COUNT)
			{
				printf("[ERROR] Network::CheckRecvFromClient, connect count limit\n");
                continue;
			}
			client_len = sizeof(client_address);
			int client_sockfd = accept(m_server_sockfd, (struct sockaddr*)&client_address, &client_len);
			FD_SET(client_sockfd, &m_readfds_from_client);
	
			ConnectItem connect_item;
			connect_item.ip = inet_ntoa(client_address.sin_addr);
			connect_item.port = ntohs(client_address.sin_port);
			connect_item.sockfd = client_sockfd;
			connect_item.valid = true;
			if (m_reuse_netid_stack.size() > 0)
			{
				connect_item.netid = m_reuse_netid_stack.top();
				m_reuse_netid_stack.pop();
				m_connect_item_list[connect_item.netid] = connect_item;
			}
			else
			{
				connect_item.netid = (int)m_connect_item_list.size();
				m_connect_item_list.push_back(connect_item);
			}

			m_sockfd_to_netid_map[client_sockfd] = connect_item.netid;
			m_callback->OnAccept(connect_item.netid);
		}	
		else {
			// 否则肯定是客户的活动。如果收到的活动是close，就说明客户已经断开，就把它关联的套接字从描述符集合中删除，否则为客户服务
			NetID netid = this->GetNetID(fd);

			int nread = 0;
			ioctl(fd, FIONREAD, &nread);
			if (nread == 0) {
				m_callback->OnDisconnect(netid);

				auto connect_item = this->GetConnectItem(netid);
				if (connect_item)
				{
					connect_item->valid = false;
					m_reuse_netid_stack.push(netid);
					m_sockfd_to_netid_map.erase(fd);
				}

				close(fd);
				FD_CLR(fd, &m_readfds_from_client);
			}
			else {
				nread = read(fd, m_buffer, sizeof(m_buffer));
				if (nread >= (int)sizeof(m_buffer)) {
					while (read(fd, m_buffer, sizeof(m_buffer))) {}
					printf("[ERROR] buffer not enough to read!!\n");
				}
				else {
					m_callback->OnRecv(netid, m_buffer, nread);
				}
			}
		}
	}
}

void Network::CheckRecvFromServer()
{
	struct timeval timeout = {0, 1}; 

	fd_set testfds = m_readfds_from_server;
	int result = select(FD_SETSIZE, &testfds, NULL, NULL, &timeout);    
	if (result == -1) 
	{   
	    perror("Network::CheckRecvFromServer select");
		return;
	}   

	if (result < 1) return;

	for (int fd = 0; fd < FD_SETSIZE; fd++)
	{
		if (!FD_ISSET(fd, &testfds)) continue;

		NetID netid = this->GetNetID(fd);

		int nread = 0;
		ioctl(fd, FIONREAD, &nread);
		if (nread == 0) {
			m_callback->OnDisconnect(netid);

			auto connect_item = this->GetConnectItem(netid);
			if (connect_item)
			{
				connect_item->valid = false;
				m_reuse_netid_stack.push(netid);
				m_sockfd_to_netid_map.erase(fd);
			}
			close(fd);
			FD_CLR(fd, &m_readfds_from_server);
		}
		else {
			nread = read(fd, m_buffer, sizeof(m_buffer));
			if (nread >= (int)sizeof(m_buffer)) {
				while (read(fd, m_buffer, sizeof(m_buffer))) {}
				printf("[ERROR] buffer not enough to read!!\n");
			}
			else {
				m_callback->OnRecv(netid, m_buffer, nread);
			}
		}
	}
}

bool Network::Listen(unsigned short port, int backlog)
{
	socklen_t server_len;
	struct sockaddr_in server_address;

	m_server_sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(port);
	server_len = sizeof(server_address);

	if (0 != bind(m_server_sockfd, (struct sockaddr*)&server_address, server_len))
	{
		perror("bind");
		return false;
	}

	if (0 != listen(m_server_sockfd, backlog))
	{
		perror("listen");
		return false;
	}

	FD_SET(m_server_sockfd, &m_readfds_from_client);

	return true;
}

NetID Network::Connect(const std::string &ip, unsigned short port)
{
	if ((int)m_sockfd_to_netid_map.size() >= MAX_CONNECT_COUNT)
	{
		printf("[ERROR] Network::Connect, connect count limit\n");
		return -1;
	}

	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip.c_str());
	address.sin_port = htons(port);
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr*)&address, len);
	if (result == -1) {
	    perror("connect");
		return -1;
	}

	ConnectItem connect_item;
	connect_item.ip = ip;
	connect_item.port = port;
	connect_item.sockfd = sockfd;
	connect_item.valid = true;
	if (m_reuse_netid_stack.size() > 0)
	{
		connect_item.netid = m_reuse_netid_stack.top();
		m_reuse_netid_stack.pop();
		m_connect_item_list[connect_item.netid] = connect_item;
	}
	else
	{
		connect_item.netid = (int)m_connect_item_list.size();
		m_connect_item_list.push_back(connect_item);
	}

	m_sockfd_to_netid_map[sockfd] = connect_item.netid;

	FD_SET(sockfd, &m_readfds_from_server);

	return connect_item.netid;
}

bool Network::Send(NetID netid, const char *msg, unsigned int length)
{
	if (netid < 0 || netid >= (int)m_connect_item_list.size())
	{
		printf("[ERROR] Network::Send netid[%d] invalid\n", netid);
		return false;
	}

	const auto &connect_item = m_connect_item_list[netid];
	if (!connect_item.valid)
	{
		printf("[ERROR] Network::Send netid[%d] invalid\n", netid);
		return false;
	}

	if (-1 == write(connect_item.sockfd, msg, length))
	{
		perror("Network::Send write");
		return false;
	}

	return true;
}

void Network::Disconnect(NetID netid)
{
	if (netid < 0 || netid >= (int)m_connect_item_list.size())
	{
		printf("[ERROR] Network::Send netid[%d] invalid\n", netid);
		return;
	}

	auto &connect_item = m_connect_item_list[netid];
	if (!connect_item.valid)
	{
		printf("[ERROR] Network::Send netid[%d] invalid\n", netid);
	}

	close(connect_item.sockfd);
	connect_item.valid = false;
	m_reuse_netid_stack.push(connect_item.netid);
	m_sockfd_to_netid_map.erase(connect_item.sockfd);
}

NetID Network::GetNetID(int sockfd) const
{
	auto it = m_sockfd_to_netid_map.find(sockfd);
	if (it == m_sockfd_to_netid_map.end())
	{
		return -1;
	}

	return it->second;
}

void Test_Network_Server()
{
	class NetworkCallback : public INetworkCallback
	{
	public:
		void OnRecv(NetID netid, const char *msg, unsigned int length) override
		{
			auto connect_item = m_network->GetConnectItem(netid);
			if (connect_item)
			{
				char buffer[1024] = {0};
				strncpy(buffer, msg, length);

				printf("[INFO] OnRecv: %s, from: %s:%d, netid: %d\n", buffer, connect_item->ip.c_str(), connect_item->port, netid);

				// ECHO
				m_network->Send(netid, msg, length);
			}
		}

		void OnAccept(NetID netid) override
		{
			auto connect_item = m_network->GetConnectItem(netid);
			if (connect_item)
			{
				printf("[INFO] OnAccept from: %s:%d, netid: %d\n", connect_item->ip.c_str(), connect_item->port, netid);
			}
		}

		void OnDisconnect(NetID netid) override
		{
			auto connect_item = m_network->GetConnectItem(netid);
			if (connect_item)
			{
				printf("[INFO] OnDisconnect from: %s:%d, netid: %d\n", connect_item->ip.c_str(), connect_item->port, netid);
			}
		}
	};

	std::shared_ptr<NetworkCallback> callback(new NetworkCallback);
	Network network(callback);
	callback->Register(&network);

	if (!network.Listen(9999))
	{
		return;
	}
	printf("[INFO] Listen succ on port 9999\n");

	HeartBeat heart_beat(10);
	heart_beat.Register(&network, &Network::CheckRecvFromClient);
	heart_beat.Run();
}

void Test_Network_Client()
{
	class NetworkCallback : public INetworkCallback
	{
	public:
		void OnRecv(NetID netid, const char *msg, unsigned int length) override
		{
			auto connect_item = m_network->GetConnectItem(netid);
			if (connect_item)
			{
				printf("[INFO] OnRecv: %s, from: %s:%d, netid: %d\n", msg, connect_item->ip.c_str(), connect_item->port, netid);
			}
		}

		void OnAccept(NetID netid) override
		{
			auto connect_item = m_network->GetConnectItem(netid);
			if (connect_item)
			{
				printf("[INFO] OnAccept from: %s:%d, netid: %d\n", connect_item->ip.c_str(), connect_item->port, netid);
			}
		}

		void OnDisconnect(NetID netid) override
		{
			auto connect_item = m_network->GetConnectItem(netid);
			if (connect_item)
			{
				printf("[INFO] OnDisconnect from: %s:%d, netid: %d\n", connect_item->ip.c_str(), connect_item->port, netid);
			}
		}
	};

	std::shared_ptr<NetworkCallback> callback(new NetworkCallback);
	Network network(callback);
	callback->Register(&network);

	NetID netid = network.Connect("127.0.0.1", 9999);
	if (-1 == netid)
	{
		return;
	}
	printf("[INFO] connect succ on 127.0.0.1:9999\n");

	std::string str;
	while (std::cin >> str)
	{
		network.CheckRecvFromServer();

		char buffer[1024] = {0};
		strncpy(buffer, str.c_str(), str.length());
		if (!network.Send(netid, buffer, strlen(buffer) + 1))
		{
			break;
		}
	}
}

}
