// 多重继承下的static_cast
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
  A a1;
  a1.m_a = 10;
  B b1;
  b1.m_b = 20;
  C c1;
  c1.m_c = 30;

  D *pA = static_cast<D *>(&a1);
  cout << "&a1: " << &a1 << endl;
  cout << "pA : " << pA << endl;
  cout << pA->m_a << " " << pA->m_b << " " << pA->m_c << " " << pA->m_d << endl;
  cout << "-------------" << endl;
  D *pB = static_cast<D *>(&b1);
  cout << "&b1: " << &b1 << endl;
  cout << "pB : " << pB << endl;
  cout << pB->m_a << " " << pB->m_b << " " << pB->m_c << " " << pB->m_d << endl;
  cout << "-------------" << endl;
  D *pC = static_cast<D *>(&c1);
  cout << "&c1: " << &c1 << endl;
  cout << "pC : " << pC << endl;
  cout << pC->m_a << " " << pC->m_b << " " << pC->m_c << " " << pC->m_d << endl;
  cout << "-------------" << endl;
}
