#include <iostream>
#include <Request.h>
#include <Response.h>
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

        std::string request_raw = client_socket->ReadAllBytes(READ_LIMIT);
        auto [request, status] = build_http_request(std::move(request_raw), doc_root);

        std:: cout << "Received: " + request.path + " - " + std::string(request.method) << std::endl;

        std::string response = build_http_response(request, status);
        client_socket->writeAllBytes(response.data(), response.size());

        std:: cout << "Responsed: " + response << std::endl;

        if (status == status::Status_200_OK && request.method == method::Method_GET) {
            client_socket->sendFile(request.path);
        }
    }
}
