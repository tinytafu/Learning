#include <iostream>
#include <typeinfo>
using std::cout, std::endl;

int main() {
  cout << "type* const" << endl;
  int a = 30;
  int *const ptr_one = &a;
  auto &ptr_one_ref = ptr_one;
  cout << typeid(ptr_one_ref).name() << endl; /*Pi*/
  (*ptr_one_ref)++; /*可通过ptr_one_ref修改指针指向的对象的数据*/
  /*ptr_one_ref = nullptr;*/ /*不可通过ptr_one_ref修改自身的数据*/
  /*ptr_one_ref被推导的类型就是int* const*/
  cout << "type* const" << endl;
}
#if 0
int main() {
  cout << "const type*" << endl;
  const int b = 20;
  const int *ptr_one = &b;
  auto &ptr_one_ref = ptr_one;
  cout << typeid(ptr_one_ref).name() << endl; /*Pki*/
  /*(*ptr_one_ref)++;*/  /*不可通过ptr_one_ref修改指向对象的数据*/
  ptr_one_ref = nullptr; /*可通过ptr_one_ref修改自身的数据*/
  /*ptr_one_ref被推导的类型就是const int*
   * 故ptr_one_ref引用所引用的类型就是const int* */
  cout << "const type*" << endl;
}
#endif
#if 0
int main() {
  cout << "type*" << endl;
  int a = 10;
  int *ptr_one = &a;
  auto &ptr_one_ref = ptr_one;
  cout << typeid(ptr_one_ref).name() << endl; /*Pi*/
  (*ptr_one_ref)++;      /*可通过别名修改指向的对象的数据*/
  ptr_one_ref = nullptr; /*通过别名修改自身的值*/
  /* ptr_one_ref被推导的类型就是int*
   * 故ptr_one_ref引用所引用的类型就是int*
   * 若在auto前加上const与auto推导的const int*可是不一样
   * 推导的const int*是利用引用不可修改指向的对象的数据
   * 加上const是不可通过引用修改自身的值*/
  cout << "type*" << endl;
}
#endif
