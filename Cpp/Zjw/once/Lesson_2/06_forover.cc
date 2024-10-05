//只指定形参类型而不指定形参名称的函数-> 哑元函数:1. 向下兼容 2. 形成函数重载
#include <iostream>
using namespace std;

void foo(int) { // 函数内部拿不到实参的数据(修改堆栈除外)
  cout << "这是哑元函数" << endl;
}

void foo() { cout << "形成重载的函数(对应形参的类型不同)" << endl; }
int main() {
  foo(10); // 必须要传实参
}
