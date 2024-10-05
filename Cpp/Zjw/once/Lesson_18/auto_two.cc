// 类型推导和引用的联合使用
#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;
int main() {
  int a = 30;
  const int b = 40;

  auto c = a;
  // auto:int c:int
  cout << "type of c is " << typeid(c).name() << endl;
  cout << "&c is " << &c << ",&a is " << &a << endl;
  c++;

  auto &d = a;
  // auto:int d:int&
  cout << "type of d is " << typeid(d).name() << endl;
  cout << "&d is " << &d << ",&a is " << &a << endl;
  a++;

  auto &e =
      b; // 这种情况也是可以自动推导出const,前提是被推导的目标对象是被const修饰且推导
         // 时带上引用
  // auto:const int e:const int&
  cout << "type of e is " << typeid(e).name() << endl;
  cout << "&e is " << &e << ",&b is " << &b << endl;
  // e++;//error
}
