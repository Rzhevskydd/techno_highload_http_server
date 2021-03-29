#ifndef HTTP_STATIC_SERVER_WORKER_H
#define HTTP_STATIC_SERVER_WORKER_H

#include <memory>
#include <utility>

#include "Socket.h"
#include "WorkQueue.h"

class Worker {
public:
    Worker(WorkQueue<std::unique_ptr<Socket>>& queue, std::string  root) : queue_(queue), root_(std::move(root)){}

    void work(bool* f_terminate, const std::string& doc_root);

private:
//    struct event* ev_;
    WorkQueue<std::unique_ptr<Socket>>& queue_;
    std::string root_;
};



#endif //HTTP_STATIC_SERVER_WORKER_H
