//左值和右值

#include <iostream>

using namespace std;
int foo() {
  return 1;
}
int main () {

  //-------具名内存 可以取地址 可以修改内存中的值 当前作用域的生命周期-> 非常左值-----
  int a = 20;
  int &b = a;
  a = 15;
  b = 18;
  //-------------------------------------------
  //-------具名内存 可以取地址 不可以修改内存中的值 当前作用域的生命周期-> 常左值-----
  const int d = 30;
  const int &c = b;


  const int &zx = 10;//常量引用可以延长右值的生命周期

 const int &func = foo();
  
 cout << "zx = " << zx << " func = " << func << endl;
}
