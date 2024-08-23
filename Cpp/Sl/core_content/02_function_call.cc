// 从指令角度掌握函数调用堆栈详细过程
#include <iostream>
using std::cout;
using std::endl;
int sum(int a, int b) {
  int temp = 0;
  temp = a + b;
  return temp;
}
int main() {
  int a = 10;
  int b = 20;

  int ret = sum(a, b);
  cout << "ret: " << ret << endl;
  return 0;
}
