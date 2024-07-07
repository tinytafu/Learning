#include <iostream>
using std::cout;
using std::endl;
namespace wd {
int num = 20;
void func() { cout << "wd::func" << endl; }
} // end of namespace wd

void test() {
  using namespace wd;
  cout << "num is " << num << endl;
  func();
}
void test1() {
  // 在当前作用于下的可见表和定义表都没有当前num的定义或者声明
  //  cout << "num is " << num << endl;
}

int main() { test(); }
