// 引用
#include <iostream>
using std::cout;
using std::endl;
int main() {
  int num = 20;
  int &ref = num;
  cout << "num is " << num << endl;
  cout << "ref is " << ref << endl;
  cout << "&num is " << &num << endl;
  cout << "&ref is " << &ref << endl;
  cout << "----------------------" << endl;
  int num2 = 200;
  // 不是修改ref引用的对象,而是对ref引用的对象num进行赋值
  ref = num2;
  cout << "num2 is " << num2 << endl;
  cout << "&num2 is " << &num2 << endl;
  cout << "num is " << num << endl;
  cout << "&num is " << &num << endl;
  cout << "ref is " << ref << endl;
  cout << "&ref is " << &ref << endl;
}
