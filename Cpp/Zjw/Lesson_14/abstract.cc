// 抽象类
#include <iostream>
using std::cout;
using std::endl;
class human {
public:
  virtual void fun() = 0;
};
class man : public human {
public:
  void foo() { cout << "hahaha" << endl; }
  virtual void fun() { cout << "man::fun()" << endl; }
};
int main() {
  // new human;
  man m1;
  m1.foo();
  m1.fun();
}
