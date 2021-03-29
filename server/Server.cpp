#include <stdexcept>
#include <csignal>
#include <iostream>

#include "Worker.h"
#include "Server.h"

void Server::run() {
    evbase_accept_ = event_base_new();
    if (evbase_accept_ == nullptr) {
        throw std::runtime_error("Unable to create socket accept event base");
    }

    initSigEvents();
    startWorkers();

    auto args = std::make_pair(evbase_accept_, std::ref(getQueue()));

    auto ev_accept = event_new(evbase_accept_, sock_.sd(), EV_READ | EV_PERSIST, onAccept, (void *) &args);
    if (ev_accept == nullptr) {
        throw std::runtime_error("Unable to create accept event");
    }

    event_add(ev_accept, nullptr);

    event_base_dispatch(evbase_accept_);
    stopWorkers();
}

void Server::kill() {
    if (event_base_loopexit(evbase_accept_, nullptr)) {
        throw std::runtime_error("Error shutting down server");
    }
}

void Server::initSigEvents() const {
    auto ev_int = event_new(evbase_accept_, SIGINT, EV_SIGNAL | EV_PERSIST, sigHandler, (void *) this);
    if (ev_int == nullptr) {
        return;
    }
    event_add(ev_int, nullptr);

    auto ev_term = event_new(evbase_accept_, SIGTERM, EV_SIGNAL | EV_PERSIST, sigHandler, (void *) this);
    if (ev_term == nullptr) {
        return;
    }
    event_add(ev_term, nullptr);
}

void Server::startWorkers() {
    for (size_t i = 0; i < num_workers_; i++) {
        std::cout << i << std::endl;
        Worker worker(queue_, "");
        bool f_terminate = false;
//        auto pair = std::make_pair(std::thread(&Worker::work, &worker, &f_terminate), f_terminate);
//        workers_.push_back(std::move(pair));
//        workers_.emplace_back(std::thread(&Worker::work, &worker, &f_terminate), f_terminate);
        workers_.emplace_back(std::thread([worker, f_terminate, this]() mutable {
            worker.work(&f_terminate, doc_root_);
        }), f_terminate);
    }
}

void Server::stopWorkers() {
    for (size_t i = 0; i < num_workers_; i++) {
        workers_[i].second = true;  // terminate flag;
    }

    for (auto & pair: workers_) {
        pair.first.join();
    }
}

