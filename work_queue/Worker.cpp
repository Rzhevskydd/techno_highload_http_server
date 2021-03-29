#include <iostream>
#include <Request.h>
#include "Worker.h"

#define READ_LIMIT 4096

void Worker::work(bool* f_terminate, const std::string& doc_root) {
    while (true) {
        bool need_terminate = *f_terminate;
        if (need_terminate) {
            break;
        }
        std::unique_ptr<Socket> client_socket;
        queue_.waitPop(client_socket);

//        char buf[1024];
//        ssize_t len = read(client_socket->sd(), buf, sizeof(buf) - 1);
//        if (len == -1 || len == 0) {
//            throw std::runtime_error(std::to_string(errno));
//            break;
//        }

        std::string request_raw = client_socket->ReadAllBytes(READ_LIMIT);
        auto [request, status] = build_http_request(std::move(request_raw), doc_root);

        std:: cout << "Received: " + request.path + " - " + std::string(request.method) << std::endl;
    }
}
