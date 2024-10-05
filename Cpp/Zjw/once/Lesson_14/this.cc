#include <iostream>
using std::cout;
using std::endl;

class A {
public:
  void foo() { this->vfunc(); }
  virtual void vfunc() { cout << "A:virtual function" << endl; }
};

class B : public A {
  void vfunc() { cout << "B:virtual function" << endl; }
};

int main() {
  // 定义一个子类对象
  B b;
  b.foo();
}
