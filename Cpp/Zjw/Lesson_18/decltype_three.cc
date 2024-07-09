// 返回值类型后置
#include <iostream>
using namespace std;
// decltype是一个编译时操作符,用于获取表达式的类型.不会实际执行表达式,只是用来检查表达式的类型
// 因此这里的警告是在未求值的上下文中,new
// char{'a'}这个表达式是有副作用的,但是在此操作符作用下 是没作用的
auto func() -> decltype(new char{'a'}) { return new char(); }
int main() {
  decltype(func()) ptr = func();
  *ptr = 'a';
  cout << *ptr << endl;
  delete ptr;
  ptr = nullptr;
}
