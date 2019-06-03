#pragma once
#include "PartnerCallback.h"

/*
    伙伴进程，可以通过一个 unix socket 进行通信
*/

#define unix_socket "partner.socket"

namespace utility {

void Test_Partner(const char* type);

enum class PartnerType {
    Server,
    Client
};

class Partner {
public:
    Partner(PartnerType type, PartnerCallback *callback);
    ~Partner();
    Partner(const Partner&) = delete;
    Partner& operator=(const Partner&) = delete;

    void Release();
    bool Start();
    void Send(const char *data, int len);

private:
    PartnerType type_;
    int listen_fd_;
    int connect_fd_;

    PartnerCallback *callback_;
};

}
