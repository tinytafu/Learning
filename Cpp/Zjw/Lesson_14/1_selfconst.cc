// 对象的自洽性和指向基类类型指针调用普通成员函数
#include <iostream>
using std::cout;
using std::endl;

class shape {
public:
  void draw() { cout << "shape::draw" << endl; }

private:
  int m_x;
  int m_y;
};

class rect : public shape {
public:
  void draw() { cout << "rect::draw" << endl; }

private:
  int m_rx;
  int m_ry;
};

class circle : public shape {
public:
  void draw() { cout << "circle::draw" << endl; }

private:
  int radius;
};

int main() {
  // 定义三个不同类类型的对象
  shape s;
  rect r;
  circle c;
  cout << "------------对象的自洽性-------------" << endl;
  s.draw();
  r.draw();
  c.draw();
  cout << "------------使用指向基类类型的指针---------" << endl;
  shape *ps = &s;
  ps->draw();
  shape *pr = &r;
  pr->draw();
  shape *pc = &c;
  pc->draw();
}
