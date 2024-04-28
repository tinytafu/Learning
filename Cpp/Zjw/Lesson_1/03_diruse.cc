//名字空间指令
#include <iostream>

namespace ns {
  int value = 0;
}
// int value = 0;
int main () {
  int value = 0;//在此作用域下定义一个与名字空间中同名的标识符value
  //使用名字空间指令
  using namespace ns;//在ns下的所有标识符在当前main函数作用域内可见. -- 可见表
  value = 10;
  std::cout << "ns::value is " << ns::value << std::endl;
}
