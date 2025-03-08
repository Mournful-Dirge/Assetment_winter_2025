#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>
#include <thread>
using namespace std;

template <typename T>
class ThreadSafeQueue
{
private:
    queue<T>* q;
    mutable mutex mtx;
    condition_variable cv;
public:
    ThreadSafeQueue () : q(new queue<T>()) {q->push(T ());};
    ThreadSafeQueue (const queue<T> &q);
    ThreadSafeQueue (const ThreadSafeQueue<T>& Queue);
    ThreadSafeQueue operator=(const ThreadSafeQueue<T>& Queue);
    ~ThreadSafeQueue() {delete q;}
    void push (T value);
    bool pop (T& value);
    void display () const;
    template <typename Rep, typename Period>
    bool pop(T &value, chrono::duration<Rep, Period> timeout);
};

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const queue<T> &q) : q(new queue<T> (q)){}

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T> &Queue)
{
    lock_guard<mutex> lock(Queue->mtx);
    this->q = new queue<T> (*Queue.q);
}

template <typename T>
ThreadSafeQueue<T> ThreadSafeQueue<T>::operator=(const ThreadSafeQueue<T> &Queue)
{
    //自赋值检查
    if (this == *Queue) 
        return *this;
    lock_guard<mutex> lock(Queue.mtx);
    lock_guard<mutex> otherLock(Queue.mtx);
    delete q;
    this->q = new queue<T> (*Queue.q);
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
void ThreadSafeQueue<T>::display() const
{
    lock_guard<mutex> lock(mtx);
    for (const auto &item : q)
    {
        cout << item << " ";
    }
    cout << endl;
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

int main()
{
    ThreadSafeQueue<int> queue;
    bool running = true;

    thread producer([&queue, &running]
                    {
        for (int i = 0; i < 5; ++i)
        {
            queue.push(i);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        running = false;
    });

    thread consumer([&queue, &running]
                    {
        while (running)
        {
            int value;
            if (queue.pop(value, chrono::seconds(1)))
                cout << "花费: " << value << endl;
            else
                cout << "超时，继续等待..." << endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
