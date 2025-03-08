#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>
#include <thread>
using namespace std;

template <typename T>
class ThreadSafeQueue {
private:
    queue<T>* q;
    mutable mutex mtx;
    condition_variable cv;
public:
    ThreadSafeQueue () : q(new queue<T>()) {};
    ThreadSafeQueue (const ThreadSafeQueue<T>& Queue);
    ThreadSafeQueue operator=(const ThreadSafeQueue<T>& Queue);
    ~ThreadSafeQueue() {delete q;}
    void push (T value);
    bool pop (T& value);
    template <typename Rep, typename Period>
    bool pop(T &value, chrono::duration<Rep, Period> timeout);
};

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T> &Queue) : q(new queue<T> (*Queue.q))
{
    lock_guard<mutex> lock(Queue.mtx);
}

template <typename T>
ThreadSafeQueue<T> ThreadSafeQueue<T>::operator=(const ThreadSafeQueue<T> &Queue)
{
    if (this != &Queue) 
    {
        lock_guard<mutex> lock(Queue.mtx);
        queue<T> temp(*Queue.q);
        {
            lock_guard<std::mutex> lock(mtx);
            delete q;
            q = new queue<T> (temp);
        }
    }
    return *this;
}

template <typename T>
void ThreadSafeQueue<T>::push(T value)
{
    lock_guard<mutex> lock(mtx);
    q->push(value);
    cv.notify_one();
}

template <typename T>
bool ThreadSafeQueue<T>::pop(T &value)
{
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [this] {return !q->empty();});
    value = move(q->front());
    q->pop();
    return true;
}

template <typename T>
template <typename Rep, typename Period>
bool ThreadSafeQueue<T>::pop(T &value, chrono::duration<Rep, Period> timeout)
{
    unique_lock<mutex> lock(mtx);
    if (!cv.wait_for(lock, timeout, [this] {return !q->empty();}))
        return false;
    value = move(q->front());  
    q->pop();
    return true;
}

int main() {
    ThreadSafeQueue<int> queue;
    bool running = true;

    std::thread producer([&queue, &running] {
        for (int i = 0; i < 5; ++i) {
            queue.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        running = false;
    });

    std::thread consumer([&queue, &running] {
        while (running) {
            int value;
            if (queue.pop(value, std::chrono::seconds(1))) {
                std::cout << "花费: " << value << std::endl;
            } else {
                std::cout << "超时，继续等待..." << std::endl;
            }
        }
    });

    producer.join();
    consumer.join();

    return 0;
}