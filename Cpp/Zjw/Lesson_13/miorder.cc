// 多重继承
#include <iostream>
using std::cout;
using std::endl;

class A {
public:
  A() { cout << "A is invoked!" << endl; }
  ~A() { cout << "~A() is invoked!" << endl; }
  int m_a;
};
class B {
public:
  B() { cout << "B is invoked!" << endl; }
  ~B() { cout << "~B() is invoked!" << endl; }
  int m_b;
};
class C {
public:
  C() { cout << "C is invoked!" << endl; }
  ~C() { cout << "~C() is invoked!" << endl; }
  int m_c;
};
class D : public A, public B, public C {
public:
  D() { cout << "D is invoked!" << endl; }
  ~D() { cout << "~D() is invoked!" << endl; }
  int m_d;
};

int main() {
  D d1;
  D *p = &d1;
  cout << "d1所占内存空间的首地址: " << p << endl;
  cout << "d1中A类子对象的首地址: " << &d1.m_a << endl;
  cout << "d1中B类子对象的首地址: " << &d1.m_b << endl;
  cout << "d1中C类子对象的首地址: " << &d1.m_c << endl;
  cout << "d1中D类中的成员地址  : " << &d1.m_d << endl;
}
