// 类型推导的局限性
#include <iostream>
#include <typeinfo>

class human {
private:
  auto i; // error
  auto that; // error以上都是声明,都没有目标对象可以利用进行推导
}
/* void func(auto f) { // c++11不支持
  std::cout << f << std::endl;
} */
int main() {
  // func(10);
}
