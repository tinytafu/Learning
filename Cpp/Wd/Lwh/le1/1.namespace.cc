/*使用作用域限定符::访问命名空间中的实体 */
#include <iostream>
using std::cout;
using std::endl;

namespace tofu {
// 变量
int val = 20;
short num = -30;
void display() { cout << "tofu::display()" << endl; }
void show() { cout << "tofu::show()" << endl; }
} // end of namespace tofu

int main() {
  cout << "tofu::val: " << tofu::val << endl;
  cout << "tofu::num: " << tofu::num << endl;
  tofu::display();
  tofu::show();
  return 0;
}
