#include "Partner.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

namespace utility {

void Test_Partner(const char* type)
{
    if (strcmp("server", type) == 0) {
        Partner server(PartnerType::Server, new PartnerCallbackEcho());
        server.Start();
    }
    else if (strcmp("client", type) == 0) {
        Partner client(PartnerType::Client, nullptr);
        client.Start();

        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            client.Send(buffer, strlen(buffer));
        }
    }
    else {
        exit(1);
    }
}

Partner::Partner(PartnerType type, PartnerCallback *callback) : 
    type_(type), 
    listen_fd_(-1), connect_fd_(-1), 
    callback_(callback)
{
}

Partner::~Partner()
{
    this->Release();
}

void Partner::Release()
{
    if (listen_fd_ >= 0) {
        close(listen_fd_);
    }

    if (connect_fd_ >= 0) {
        close(connect_fd_);
        connect_fd_ = -1;
    }

    if (callback_) {
        delete callback_;
        callback_ = nullptr;
    }
}

bool Partner::Start()
{
    if (type_ == PartnerType::Server) {
        listen_fd_ = socket(AF_UNIX, SOCK_STREAM, 0);

        struct sockaddr_un server_address;
        server_address.sun_family = AF_UNIX;
        strcpy(server_address.sun_path, unix_socket);

        int res = bind(listen_fd_, (struct sockaddr*)&server_address, sizeof(server_address));
        if (res != 0) {
            perror("Partner Server bind");
            return false;
        }

        res = listen(listen_fd_, 1);
        if (res != 0) {
            perror("Partner Server listen");
            return false;
        }

        struct sockaddr_un client_address;
        socklen_t client_len = sizeof(client_address);

        connect_fd_ = accept(listen_fd_, (struct sockaddr*)&client_address, &client_len);
        if (connect_fd_ == -1) {
            perror("Parnter Server accept");
            return false;
        }

        char buffer[4096];
        while (true) {
            int read_len = read(connect_fd_, buffer, sizeof(buffer));
            if (read_len <= 0) {
                if (read_len == 0) {
                    printf("Parnter closed\n");
                }
                break;
            }
            if (callback_)
                callback_->OnRecv(buffer, read_len);
        }

        unlink(unix_socket);
    }
    else if (type_ == PartnerType::Client) {
        struct sockaddr_un address;
        connect_fd_ = socket(AF_UNIX, SOCK_STREAM, 0);

        address.sun_family = AF_UNIX;
        strcpy(address.sun_path, unix_socket);

        int res = connect(connect_fd_, (struct sockaddr*)&address, sizeof(address));
        if (res == -1) {
            perror("Partner connect");
            return false;
        }
    }
    else {
        return false;
    }

    return true;
}

void Partner::Send(const char *data, int len)
{
    if (type_ == PartnerType::Client) {
        if (connect_fd_ > 0) {
            write(connect_fd_, data, len);
        }
    }
}

}
