// 对象的自洽性和指向基类类型指针调用普通成员函数
#include <iostream>
using std::cout;
using std::endl;

class shape {
public:
  virtual void draw() { cout << "shape::draw" << endl; }

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
  // 利用对象调用虚函数
  shape s;
  s.draw();
  rect r;
  r.draw();
  circle c;
  c.draw();
  cout << "sizeof(s) is " << sizeof(s) << endl;
  cout << "sizeof(r) is " << sizeof(r) << endl;
  cout << "sizeof(c) is " << sizeof(c) << endl;
  // 利用指向基类类型的指针调用虚函数
  shape *ps = &s;
  ps->draw();
  shape *pr = &r;
  pr->draw();
  shape *pc = &c;
  pc->draw();
}
