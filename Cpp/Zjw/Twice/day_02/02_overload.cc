// 函数之间的关系 -- 重载(1.同一作用域2.函数名相同3.形参表不同)
// 形参表不同决定于形参的个数和每个对应形参的不同
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

//void foo(double d,int i){} //形参名不同的函数构成不了重载关系
//int foo(int inum,double dnum){} // 函数的重载与返回值无关

int main (){
  char* name = nullptr;
  short age = 20;
  foo(name,age);
  char const *title = "wangshuai";
  foo(title,age);
  int var = 10;
  double dou = 20.2;
  foo(var,dou);
  foo(dou,var);
}
