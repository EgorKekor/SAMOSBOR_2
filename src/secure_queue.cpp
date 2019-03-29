#include <secure_queue.h>
template <typename T>
bool secure_queue<T>::empty() {
    mut.lock();
    bool result = que.empty();
    mut.unlock();
    return result;
}

template <typename T>
void secure_queue<T>::pop() {
    mut.lock();
    que.pop();
    mut.unlock();
    return;
}

template <typename T>
const T& secure_queue<T>::front() {
    mut.lock();
    const T & result = que.front();
    mut.unlock();
    return result;
}

template <typename T>
void secure_queue<T>::push(const T & input) {
    mut.lock();
    que.push(input);
    mut.unlock();
}

