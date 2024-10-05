// 多重继承下的类型转换
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
  d1.m_a = 10;
  d1.m_b = 20;
  // 将子类对象的地址赋值给指向基类A的指针变量
  A *pa = &d1;
  cout << "pa      = " << (void *)pa << endl;
  cout << "&d1.m_a = " << (void *)&d1.m_a << endl;
  cout << "----------------------------" << endl;
  // 将子类对象的地址赋值给指向基类B的指针变量
  B *pb = &d1;
  cout << "pb      = " << (void *)pb << endl;
  cout << "&d1.m_b = " << (void *)&d1.m_b << endl;
  cout << "----------------------------" << endl;
  // 将子类对象的地址赋值给指向基类C的指针变量
  C *pc = &d1;
  cout << "pc      = " << (void *)pc << endl;
  cout << "&d1.m_c = " << (void *)&d1.m_c << endl;

  /*--------------静态转换--------------*/
  D *pd = static_cast<D *>(pa);
  cout << "A*->D*,pd:" << pd << endl;
  pd = static_cast<D *>(pb);
  cout << "B*->D*,pd:" << pd << endl;
  pd = static_cast<D *>(pc);
  cout << "C*->D*,pd:" << pd << endl;

  /*-------------重解释转换-------------*/
  pa = reinterpret_cast<A *>(&d1);
  cout << "pa:" << pa << endl;
  pb = reinterpret_cast<B *>(&d1);
  cout << "pb:" << pa << endl;
  pc = reinterpret_cast<C *>(&d1);
  cout << "pc:" << pa << endl;
}
