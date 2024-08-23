/*3.使用using声明*/
#include <iostream>
using std::cout;
using std::endl;

namespace tofu {
void show();
int value = 100;
double score = 99.99;
void display() {
  cout << "tofu::display()" << endl;
  show();
}
void show() { cout << "tofu::show()" << endl; }
} // namespace tofu

int main() {
  /*将tofu中的value实体引入当前作用域内,相当于定义*/
  using tofu::value;
  cout << value << endl;
  return 0;
}
