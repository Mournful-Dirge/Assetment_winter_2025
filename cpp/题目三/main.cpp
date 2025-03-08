#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;
mutex mtx;

template <typename T>
class ThreadSafeQueue {
private:
    queue<T>* q;
public:
    ThreadSafeQueue ();
    ThreadSafeQueue (const queue<T> &q);
    ThreadSafeQueue (const ThreadSafeQueue<T> &Queue);
    ThreadSafeQueue<T> operator = (const ThreadSafeQueue<T> &Queue);
    ~ThreadSafeQueue ();
    void push (T value);
    bool pop (T &value);
    void display () const;
};

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue() : q(new queue<T> ())
{
    q->push(T ());
}

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const queue<T> &q) : q(new queue<T> ()){}

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue<T> &Queue)
{
    this->q = new queue<T> (*Queue.q);
}

template <typename T>
ThreadSafeQueue<T> ThreadSafeQueue<T>::operator=(const ThreadSafeQueue<T> &Queue)
{
    //自赋值检查
    if (this == *Queue) 
        return *this;

    delete q;
    this->q = new queue<T> (*Queue.q);
    return *this;
}

template <typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue()
{
    delete q;
}

template <typename T>
void ThreadSafeQueue<T>::push(T value)
{
    q->back() = value;  
}

template <typename T>
bool ThreadSafeQueue<T>::pop(T &value)
{
    q->pop()
}

template <typename T>
void ThreadSafeQueue<T>::display() const
{
    if (q->empty())
        cout << "队列为空" << endl;
    else 
    {
        cout << "队列有" << q->size() << "个元素，依次为：" << endl;
        queue<T>* Q = new queue<T>
    }
}
