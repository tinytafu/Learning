//名字空间声明

#include <iostream>

namespace ns{
  int value = 0;
}
// int value = 10;
int main () {
  // int value = 10;
  //使用名字空间声明
  using ns::value;//将名字空间ns中的value引入当前作用域(相当于定义)

  value = 800;
  std::cout << "ns::value is " << ns::value << std::endl;
}
