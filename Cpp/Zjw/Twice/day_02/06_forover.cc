//哑元函数
#include <iostream>

void foo(int){
  /*函数内部使用不到传入的实参*/
  /*但是调用者调用哑元函数是需要传入参数的*/
  std::cout << "foo(int)" << std::endl;
}

int main () {
  foo(10);
  return 0;
}
