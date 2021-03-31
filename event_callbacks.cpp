#include <iostream>
#include <cstring>
#include "Server.h"

void sigHandler(int signal, short events, void *args) {
    std::cout << "Received signal" + std::to_string(signal) + ":" + strsignal(signal) + "Shutting down." << std::endl;
    auto server = reinterpret_cast<Server*>(args);
    server->kill();
}

void onAccept(int fd, short events, void *args) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    auto args_ptr = reinterpret_cast<OnAcceptArgsType*>(args);
    auto ev_base = args_ptr->first;
    auto& work_queue = args_ptr->second;

    int client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        throw std::runtime_error("accept failed");
    }

//    work_queue.push(std::make_unique<Socket>(client_fd));

//    auto wrapped_queue_ref = std::ref(work_queue);
//    auto client_ev_read = event_new(ev_base, client_fd, EV_READ, onRead, (void *) &wrapped_queue_ref);
    auto client_ev_read = event_new(ev_base, client_fd, EV_READ, onRead, (void *) &work_queue);

    event_add(client_ev_read, nullptr);
}

void onRead(int fd, short events, void *args) {
    auto queue_ptr = reinterpret_cast<WorkQueueType *>(args);
    if (!queue_ptr) {
        return;
    }
    queue_ptr->push(std::make_unique<Socket>(fd));
}
