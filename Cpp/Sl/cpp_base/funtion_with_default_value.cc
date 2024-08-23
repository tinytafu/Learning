// 形式参数带默认值的函数
#include <iostream>
using std::cout;
using std::endl;
// 形参带默认值的函数
int sum(int a = 10, int b = 20) { return a + b; }
int main() {
  int a = 10;
  int b = 20;

  /*int ret = sum(a, b);*/
  int ret = sum();
  cout << ret << endl;
  return 0;
}
