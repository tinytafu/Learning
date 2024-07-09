// 返回值类型后置
#include <iostream>
#include <typeinfo>
using namespace std;
auto func() -> decltype(new char{'a'}) { return new char(); }
int main() {
  decltype(func()) ptr = func();
  *ptr = 'a';
  cout << *ptr << endl;
  delete ptr;
  ptr = nullptr;
}
