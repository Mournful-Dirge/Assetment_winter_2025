# CPP 任务

## 题目一

```cpp
题目：实现一个简单的类
编写一个C++类 Rectangle，表示矩形。要求：

包含两个私有成员变量：width 和 height。

提供构造函数、拷贝构造函数、赋值运算符重载。

提供成员函数 area()，计算矩形的面积。

提供成员函数 resize(double scale)，按比例缩放矩形的宽度和高度。

提供友元函数 bool isSquare(const Rectangle& rect)，判断矩形是否为正方形。题目：实现一个简单的类
```

编写一个C++类 Rectangle，表示矩形。要求：

+ 包含两个私有成员变量：width 和 height。
+ 提供构造函数、拷贝构造函数、赋值运算符重载。
+ 提供成员函数 area()，计算矩形的面积。
+ 提供成员函数 resize(double scale)，按比例缩放矩形的宽度和高度。
+ 提供友元函数 bool isSquare(const Rectangle& rect)，判断矩形是否为正方形。

## 题目二

```cpp
题目：实现一个通用的栈类
编写一个模板类 Stack<T>，表示一个后进先出（LIFO）的栈。要求：

支持动态扩容。

提供 push(T value)、pop()、top()、isEmpty() 等基本操作。

提供拷贝构造函数和赋值运算符重载，确保深拷贝。

提供 size() 函数，返回当前栈中元素的数量。

```

### (可选)支持迭代器，可以使用范围for循环遍历栈可选）支持迭代器，可以使用范围for循环遍历栈

## 题目三  多线程

```cpp
编写一个模板类 ThreadSafeQueue<T>，表示一个线程安全的队列。要求：

使用 std::queue 作为底层容器。

使用 std::mutex 和 std::condition_variable 实现线程安全。

提供 push(T value) 和 bool pop(T& value) 函数，分别用于入队和出队。

pop 函数在队列为空时应阻塞，直到有新元素入队。
```

### (可选)支持超时机制，pop 函数在指定时间内未获取到元素时返回 false

## 题目四

详见communicate文件夹
