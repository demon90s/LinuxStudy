#ifndef NETWORK_H
#define NETWORK_H

#include <sys/types.h>
#include <memory>
#include <vector>
#include <stack>
#include <map>
#include <string>

namespace utility
{

extern void Test_Network_Server();
extern void Test_Network_Client();

typedef int NetID;

/*
 * 使用select实现异步TCP网络连接模型
 * 通过一个整数NetID作为连接句柄
 * 最多保持512个连接（不超过FD_SETSIZE）
 */

class Network;

class INetworkCallback
{
public:
	INetworkCallback() : m_network(nullptr) {}
	virtual ~INetworkCallback() {}

	void Register(Network *network) { m_network = network; }

	virtual void OnRecv(NetID, const char *msg, unsigned int length) {}

	virtual void OnAccept(NetID netid) {}

	virtual void OnDisconnect(NetID netid) {}

protected:
	Network *m_network;
};

class Network
{
public:
	struct ConnectItem
	{
		NetID netid = -1;
		std::string ip;
		unsigned short port = 0;
		int sockfd = -1;
		bool valid = false;
	};

	Network(std::shared_ptr<INetworkCallback> callback);
	~Network();

	ConnectItem* GetConnectItem(NetID netid);

	void CheckRecvFromClient();
	void CheckRecvFromServer();

	bool Listen(unsigned short port = 12345, int backlog = 5);

	NetID Connect(const std::string &ip, unsigned short port);

	void Disconnect(NetID netid);

	bool Send(NetID netid, const char *msg, unsigned int length);

private:
	int m_server_sockfd;
	fd_set m_readfds_from_client;
	fd_set m_readfds_from_server;
	char m_buffer[1024 * 1024]; // 最多收发1MB数据

	std::shared_ptr<INetworkCallback> m_callback;

private:
	std::vector<ConnectItem> m_connect_item_list;
	std::stack<NetID> m_reuse_netid_stack;
	std::map<int, NetID> m_sockfd_to_netid_map;

	NetID GetNetID(int sockfd) const;
};

}

#endif // NETWORK_H
