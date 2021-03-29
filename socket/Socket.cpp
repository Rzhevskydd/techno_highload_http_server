#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <stdexcept>
#include <arpa/inet.h>
#include <sstream>

#include "Server.h"
#include "Socket.h"

bool checkHostIsLocalAddr(std::string &host) {
    return true; // todo
}

void Socket::setReuseAddr(int sd) {
    int yes = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        ::close(sd);
        throw std::runtime_error("setopt: " + std::string(strerror(errno)));
    }
}

void Socket::makeServerSocket(std::string &host, uint16_t port) {
    int sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0) {
        throw std::runtime_error("socket: " + std::string(strerror(errno)));
    }
    setReuseAddr(sd);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    if (checkHostIsLocalAddr(host)) {
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // inet_addr("0.0.0.0");
    } else {
        serv_addr.sin_addr.s_addr = inet_addr(host.c_str());
    }

    // serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serv_addr.sin_port = htons(port);

    if (::bind(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        ::close(sd);
        throw std::runtime_error("bind: " + std::string(strerror(errno)));
    }
    ::listen(sd, DEFAULT_LISTEN_QUEUE_SIZE);
    sd_ = sd;
}

std::string Socket::ReadAllBytes(size_t limit) {
    std::ostringstream sstream;
    while (sstream.tellp() < limit) {
        std::string s_buf(1024, '\0');
        size_t bytes_read = Read(s_buf.data(), s_buf.size());

        sstream.write(s_buf.c_str(), static_cast<long>(bytes_read));

        if (bytes_read < s_buf.size()) {
            break;
        }
    }
    return sstream.str();
}

size_t Socket::Read(void *buf, size_t chunk_size) {
    while(true) {
        ssize_t bytes_read = read(sd_, buf, chunk_size);

        if (bytes_read < 0) {
            if (errno == EINTR) {
                std::cout << "Interrupted system call" <<std::endl;
                continue;
            }
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                std::cout << "Operation would block" <<std::endl;
                return 0;
            }
            throw std::runtime_error("Cannot read from socket");
        }
        return static_cast<size_t>(bytes_read);
    }
}
