#ifndef HTTP_STATIC_SERVER_SOCKET_H
#define HTTP_STATIC_SERVER_SOCKET_H

#include <unistd.h>  // close()
#include <string>
#include <iostream>

class Socket {
public:
    Socket() : sd_(-1) {};
    Socket(int fd) : sd_(fd) {};
    ~Socket() {
        if (sd_ > 0) {
            std::cout << "Close socket" + std::to_string(sd_) << std::endl;
            ::close(sd_);
        }
    }

public:
    int sd() const noexcept { return sd_; }

    void makeServerSocket(std::string& host, uint16_t port);
    void setReuseAddr(int sd);

    std::string ReadAllBytes(size_t limit);
    size_t Read(void *buf, size_t chunk_size);

private:
    int sd_;

};


#endif //HTTP_STATIC_SERVER_SOCKET_H
