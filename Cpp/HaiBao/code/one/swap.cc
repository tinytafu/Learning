// 交换两个变量的值
#include <iostream>
using namespace std;
namespace condition {
// 值传递.传递的是数值
void swap(int x, int y) {
  int tmp = x;
  x = y;
  y = tmp;
}
// 值传递,传递的是地址
void swap(int *x, int *y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}
} // end of namespace condition

namespace modern {
// 引用传递,只是传递对象的别名
void swap(int &x, int &y) {
  int tmp = x;
  x = y;
  y = tmp;
}
} // end of namespace modern
int main() {
  int a = 20;
  int b = 30;
  condition::swap(a, b);
  cout << a << endl;
  cout << b << endl;
  cout << "-----------------" << endl;
  condition::swap(&a, &b);
  cout << a << endl;
  cout << b << endl;
  cout << "-----------------" << endl;
  modern::swap(a, b);
  cout << a << endl;
  cout << b << endl;
}
