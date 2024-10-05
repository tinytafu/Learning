// 普通方式调用重载函数 -> 实参与形参类型的匹配度
// 函数指针方式调用重载函数 -> 由决定函数指针类型中的形参类型决定的
#include <iostream>
using std::cout;

void foo(char* name,short age){
  cout << "1.foo" << "\n";
}
void foo(int inum,double dnum){
  cout << "2.foo" << "\n";
}
void foo(char const *cname,short sage){
  cout << "3.foo" << "\n";
}
void foo(double dnum,int inum){
  cout << "4.foo" << "\n";
}
/*void foo(...){*/
/*  cout << "5.foo" << "\n";*/
/*}*/

int main (){
  /*普通方式调用*/
  double dou = 20.2;
  short var = 20;
  foo(dou,var);/*匹配的是升级转换 小类型向大类型转 不丢失精度*/

  /*函数指针*/
  void (*pfun)(double,int) = foo;
  pfun(dou,var);
  return 0;
}
