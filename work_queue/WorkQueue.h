#ifndef HTTP_STATIC_SERVER_WORKQUEUE_H
#define HTTP_STATIC_SERVER_WORKQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class WorkQueue {
public:
    bool push(T val) {
        std::lock_guard<std::mutex> guard(mu_);
        q_.push(std::move(val));
        cv_.notify_one();
        return true;
    }

    bool waitPop(T& val) {
        std::unique_lock<std::mutex> guard(mu_);
        cv_.wait(guard, [this]() {
            return !q_.empty();
        });
        val = std::move(q_.front());
        q_.pop();
        return false;
    }

private:
    std::queue<T> q_;
    mutable std::mutex mu_;
    std::condition_variable cv_;
};


#endif //HTTP_STATIC_SERVER_WORKQUEUE_H
