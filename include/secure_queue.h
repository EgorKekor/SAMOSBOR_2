#ifndef SECURE_QUEUE_H
#define SECURE_QUEUE_H
#include <queue>
#include <mutex>

template <typename T>
class secure_queue {
 public:
    bool empty();
    void pop();
    const T& front();
    void push(const T&);
    void lock();
    void unlock();
 private:
    std::recursive_mutex mut;
    std::queue<T> que;
};
#endif
