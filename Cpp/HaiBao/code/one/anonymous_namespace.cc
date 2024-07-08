// 匿名命名空间
#include <iostream>
using std::cout;
using std::endl;
namespace {
int value = 300;
void func() { cout << value << endl; }
} // end of namespace

int main() {
  cout << value << endl;
  func();
}
