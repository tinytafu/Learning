// 类新计算的四种规则
#include <iostream>
#include <typeinfo>
using namespace std;

const char *func() { return new char{'a'}; }
int main() {
  /*1.如果给定的表达式是一个标识符表达式,那么编译器将根据标识符本身的类型作为最终计算出的类型*/
  const int &a = 20;
  decltype(a) b = a;
  // decltype:const int& b:const int&
  cout << "type of b is " << typeid(b).name() << endl;
  cout << "&b is " << &b << "\n&a is " << &a << endl;
  // b++;error不允许修改

  /*2.如果给定的表达式是一个函数表达式,编译器将根据函数返回值的类型作为最终计算出的类型*/
  decltype(func()) ptr = func();
  // decltype:PKc pointer const char = const char*
  cout << "type of ptr is " << typeid(ptr).name() << endl;
  cout << "ptr is " << ptr << "func is " << func() << endl;

  /*3.如果给定的是其他表达式,若这个表达式的结果是一个左值,那么编译器将该左值引用的类型
   * 作为最终计算出的类型*/
  int num = 30;
  decltype(++num) val = num;
  // decltype:int&
  cout << "type of val is " << typeid(val).name() << endl;    // i
  cout << "&val is " << &val << "\n&num is " << &num << endl; // 地址一样
  val++;                                                      // 可以修改

  /*4.如果给定的是其他表达式,若这个表达式的结果是一个右值,那么编译器将该右值的类型
   * 作为最终计算出的类型*/
  decltype(num++) value = num;
  cout << "type of value is " << typeid(value).name() << endl;    // i
  cout << "&value is " << &value << "\n&num is " << &num << endl; // 地址一样
  value++; // 可以修改
}
