/*2.使用using指令*/
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
  /*将tofu中的所有实体引入当前作用域,在当前作用域内可见*/
  using namespace tofu;
  cout << value << endl;
  cout << score << endl;
  show();
  display();
  return 0;
}
