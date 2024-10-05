#include <iostream>
#include <typeinfo>
using std::cout, std::endl, std::string;

int main() {
  int val = 10;
  auto &auto_val = val;
  cout << typeid(auto_val).name() << endl;
  auto_val++;
  cout << "&val:" << &val << ", &auto_val:" << &auto_val << endl;
#if 1
  const int a = 10;
  auto b = a;
  // 1.检查b的类型是什么
  cout << typeid(b).name() << endl; // int
  // 2.auto推导的类型是否被const修饰
  b++; // 可以修改,没有const修饰
  // b的类型是int,const此时影响不了a的类型
  const int *ptr_one = &a;
  auto ptr_two = ptr_one;
  // 1.检查ptr_two的类型是什么
  cout << typeid(ptr_two).name() << endl; // Pki
  // 2.是否被const修饰,检查是否可以更改ptr_two指向的对象或者ptr_two本身
  //(*ptr_two)++;//指向的对象不可以被修改
  ptr_two = nullptr; // 指针本身可以修改
  // ptr_two的类型是const int*,const此时是影响ptr_two的类型的

  int *ptr_ws = &b;
  auto &ptr_ref = ptr_ws;
  cout << typeid(ptr_ref).name() << endl;
  ptr_ws = nullptr;
  (*ptr_ws) = 0;
  int *const ptr_three = &b;
  auto ptr_four = ptr_three;
  // 1.检查ptr_three的类型
  cout << typeid(ptr_four).name() << endl; // Pi
  // 2.检查ptr_three指向的对象是否可以修改,或者ptr_three本身是否可以修改
  (*ptr_three)++;     // 可以修改指向的对象
  ptr_four = nullptr; // 可以修改自身
  // ptr_four的类型是int* const此时是不影响ptr_three的类型
  int *const ptr_five = &b;
  auto &ptr_six = ptr_five;
  cout << typeid(ptr_six).name() << endl;
  /*ptr_six = &b;*/
  (*ptr_six)++;
  const int *ptr_seven = &a;
  auto &ptr_eight = ptr_seven;
  cout << typeid(ptr_eight).name() << endl;
  ptr_eight = nullptr;
  /*const int *&ptr_a = ptr_four;*/
  /*(*ptr_eight)++;*/
#endif
}
