// 缺省(默认)参数:在函数声明中指定函数形参默认值的参数叫作缺省参数
#include <iostream>
using namespace std;

/*当函数中一个形参被指定为缺省参数,那么此参数后的所有形参都必须指定为缺省参数*/
/*函数缺省参数只能在函数声明中指定,函数定义中不可以*/
void foo(int a, short b = 10, float fl = 22.24f, double dou = 34.44) {
  cout << "a is " << a << "\nb is " << b << "\nfl is " << fl << "\ndou is " << dou
       << endl;
}

/*避免使用函数缺省参数 可能会导致重载歧义,导致编译器不知道选哪个函数调用*/
// void foo(int a){
//   cout <<"导致歧义" << endl;
// }
int main() { 
  foo(10);//不知道调用哪一个 
}
