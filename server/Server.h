#ifndef HTTP_STATIC_SERVER_SERVER_H
#define HTTP_STATIC_SERVER_SERVER_H

#include <cstdio>
#include <string>
#include <event2/event.h>
#include <vector>
#include <thread>

#include "Socket.h"
#include "WorkQueue.h"

#define DEFAULT_LISTEN_QUEUE_SIZE 1000

void onAccept(int fd, short events, void *args);
void OnRead(int fd, short events, void *args);
void sigHandler(int signal, short events, void *args);

using WorkQueueType = WorkQueue<std::unique_ptr<Socket>>;
using OnAcceptArgsType = std::pair<std::__decay_and_strip<event_base * &>::__type, WorkQueue<std::unique_ptr<Socket>> &>;

class Server {
public:
    Server(std::string& host, uint16_t port, std::size_t n_workers) :
    num_workers_(n_workers), evbase_accept_(nullptr), queue_() {
        sock_.makeServerSocket(host, port);
    };

    void run();
    void kill();

private:
    WorkQueue<std::unique_ptr<Socket>>& getQueue() { return queue_; }
    void initSigEvents() const;
    void startWorkers();
    void stopWorkers();

    Socket sock_;
    event_base* evbase_accept_;
    std::size_t num_workers_;
    std::string doc_root_;

    WorkQueue<std::unique_ptr<Socket>> queue_;

    using terminated_thread = std::pair<std::thread, bool>;
    std::vector<terminated_thread> workers_;

};


#endif //HTTP_STATIC_SERVER_SERVER_H
