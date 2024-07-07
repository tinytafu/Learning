// 命名空间 -- namespace
#include <iostream>
using std::cout;
using std::endl;

namespace wd {
int num = 100;
void func() { cout << "wd::func" << endl; }
} // end of namespace wd
namespace hw {
int num = 200;
void func() { cout << "hw::func" << endl; }
} // end of namespace hw

void test() {
  wd::func();
  hw::func();
}
void test1() {
  // 当前作用域下的可见
  using namespace hw;
  using namespace wd;
  // func();//ambiguous
}
void test2() {
  // 相当于当前作用域下的定义
  using hw::func;
  // 当前作用于下可见
  using namespace wd;
  func();
}
int main() { test2(); }
