/*内联函数:编译器的一种优化策略*/
#include <iostream>
using namespace std;
inline void foo() {
  cout << "期望这个函数使用内联" << endl;
}

int main () {
  foo();//将此处原来的跳转指令替换为编译器编译好的foo函数二进制代码
  foo();
}
