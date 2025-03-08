#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Stack {
public:
    Stack ();
    Stack (const vector <T> &vec);
    Stack (const Stack &sta);
    Stack<T> & operator = (const Stack &sta);
    ~Stack ();
    void push (T value);
    void pop ();
    T top () const;
    bool isEmpty () const;
    int size () const;
    void display () const;

private:
    vector<T>* vec;

};

template <typename T>
Stack<T>::Stack() : vec(new vector<T> ())
{
    vec->push_back(T());
}

template <typename T>
Stack<T>::Stack(const vector<T> &vec) : vec(new vector<T> (vec)){}

template <typename T>
Stack<T>::Stack(const Stack<T> &sta)
{
    this->vec = new vector<T> (*sta.vec);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &sta)
{
    //自赋值检查
    if (this == &sta)
        return *this;

    delete vec;
    this->vec = new vector<T> (*sta.vec);
    return *this;
}

template <typename T>
Stack<T>::~Stack()
{
    delete vec;
}

template <typename T>
void Stack<T>::push(T value)
{
    vec->push_back(value);
}

template <typename T>
void Stack<T>::pop()
{
    if (vec->empty()) {
        throw out_of_range("栈为空,错误操作");
    }
    vec->pop_back();
}

template <typename T>
T Stack<T>::top() const
{
    if (vec->empty()) {
        throw out_of_range("栈为空,错误操作");
    }
    return vec->back();
}

template <typename T>
bool Stack<T>::isEmpty() const
{
    return vec->empty();
}

template <typename T>
int Stack<T>::size() const
{
    return vec->size();
}

template <typename T>
void Stack<T>::display() const
{
    if (isEmpty()) {
        cout << "栈为空";
    }
    else {
        cout << "栈一共有" << vec->size() << "个元素，依次为：" << endl;
        for (auto it = vec->begin(); it != vec->end(); it++) {
            cout << *it << "  ";
        }
    }
    cout << endl;
}

//测试代码
int main () {
    cout << "------------------------" << endl;
    cout << "默认栈构造：" << endl;
    Stack<int> sta1;
    sta1.display();
    
    cout << "------------------------" << endl;
    cout << "自定义栈构造：" << endl;
    vector<int> vec1 = {1,2,3,4,5};
    Stack sta2 (vec1);
    sta2.display();
    
    cout << "------------------------" << endl;
    cout << "通过拷贝构造函数构造栈：" << endl;
    Stack sta3 (sta2);
    sta2.display();

    cout << "------------------------" << endl;
    cout << "通过赋值运算符重载构造栈：" << endl;
    vector<int> vec2 = {5, 6, 7, 8, 9};
    Stack sta4 = vec2;
    sta4.display();
    sta4 = sta3;
    sta4.display();

    cout << "------------------------" << endl;
    cout << "入栈：" << endl;
    sta1.push(1);
    sta1.display();
    sta2.push(6);
    sta2.display();

    cout << "------------------------" << endl;
    cout << "出栈：" << endl;
    sta1.pop();
    sta1.display();
    sta2.pop();
    sta2.display();

    cout << "------------------------" << endl;
    cout << "展示栈顶元素：" << endl;
    cout << sta1.top() << endl;
    cout << sta2.top() << endl;
    cout << "------------------------" << endl;


    return 0;
}