#include <iostream>

using namespace std;

class Rectangle {
public:
    Rectangle (double width = 1.0, double height = 1.0);
    Rectangle (const Rectangle& rect);
    Rectangle& operator = (const Rectangle& rect);
    double area () const;
    void resize (double scale);    //#默认参数为正数
    friend bool isSquare (const Rectangle& rect);
    void display () const;

private:
    double width;
    double height;
};

Rectangle::Rectangle(double width, double height) : width (width), height (height) {}

Rectangle::Rectangle(const Rectangle& rect)
{
    this->width = rect.width;
    this->height = rect.height;
}

Rectangle &Rectangle::operator=(const Rectangle &rect)
{
    //自赋值检查
    if (this == &rect) {
        return *this;
    }

    height = rect.height;
    width = rect.width;
    return *this;
}

double Rectangle::area() const
{
    return width * height;
}

void Rectangle::resize(double scale)
{
    width *= scale;
    height *= scale;
}

bool isSquare(const Rectangle& rect)
{
    return rect.width == rect.height;
}

void Rectangle::display() const
{
    cout << "矩形的宽为" << width 
    << "，高为" << height << "，面积是"
    << area();
    if (isSquare(*this)) {
        cout << ",是正方形。" << endl;
    }
    else {
        cout << ",不是正方形。" << endl;
    }
}

//测试代码
int main () {
    cout << "-----------------------------------------" << endl;
    cout << "构造默认矩形：" << endl;
    Rectangle rect1;
    rect1.display();
    cout << "-----------------------------------------" << endl;

    cout << "构造自定义矩形：" << endl;
    Rectangle rect2(4.0, 5.0);
    rect2.display();
    cout << "-----------------------------------------" << endl;

    cout << "构造自定义正方形：" << endl;
    Rectangle rect3(3.0, 3.0);
    rect3.display();
    cout << "-----------------------------------------" << endl;

    cout << "缩放后的矩形：" << endl;
    rect1.resize(2.0);
    rect1.display();
    rect2.resize(2.0);
    rect2.display();
    rect3.resize(2.0);
    rect3.display();
    cout << "-----------------------------------------" << endl;
    
    cout << "通过拷贝构造函数创建的矩形：" << endl;
    Rectangle rect4 (rect2);
    rect4.display();
    cout << "-----------------------------------------" << endl;
    
    cout << "通过赋值运算符重载创建的矩形：" << endl;
    rect2 = {6.0, 9.0};
    rect2.display();
    Rectangle rect5 = {7.0, 8.0};
    rect5.display();
    rect4 = rect3;
    rect4.display();
    cout << "-----------------------------------------" << endl;

    return 0;
}