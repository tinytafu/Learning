// 虚函数表
#include <iostream>
using std::cout;
using std::endl;

class A {
public:
  virtual int int_vfunc(const int *p) {
    cout << "A:int_vfunc" << endl;
    return 1;
  }
  virtual double dou_vfunc(const double *p) {
    cout << "A:dou_vfunc" << endl;
    return 1.1;
  }
  int m_a;
  int m_b;
};
class B : public A {
public:
  virtual void func() { cout << "B:func" << endl; }
};

int main() {
  int var = 10;
  double dou = 20.2;
  A a;
  B b;
  cout << sizeof(a) << endl;
  cout << sizeof(b) << endl;
  // 如何拿到A类中指向虚函数表的指针
  int (**pfunc)(const int *p) = *(int (***)(const int *P))(&a);
  pfunc[0](&var);
  ((double (**)(const double *p))(pfunc + 1))[0](&dou);
}
