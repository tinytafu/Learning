// 类型推导和类型计算的差别
// 1.类型计算比类型推导更加精准 2.类型计算在初始值这一块会更加灵活
#include <iostream>
#include <typeinfo>
using namespace std;
int main() {
  const int a = 20;

  auto b = a;
  // auto:int b:int
  cout << "type of b is " << typeid(b).name() << endl; // i
  cout << "&b is " << &b << ",&a is" << &a << endl;    // 地址不同
  b++;                                                 // 可以修改

  decltype(a) c = a;
  // decltype:const int c:const int
  cout << "type of c is " << typeid(c).name() << endl; // i
  cout << "&c is " << &c << ",&a is " << &a << endl;   // 地址不同
  // c++;error不可以修改,是const

  // decltype在类型计算时会更加灵活,初始值不一定是非要是要计算的目标对象的初始值
  decltype(a) d = 2000;
  cout << "type of d is " << typeid(d).name() << endl;
  cout << "&d is " << &d << ",&a is " << &a << endl;
  // d++;error,不允许修改
}
