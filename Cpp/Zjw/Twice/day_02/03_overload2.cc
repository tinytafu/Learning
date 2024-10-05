// 详谈同一个作用域下
#include <iostream>
using std::cout;

namespace ns1{
void foo(char* name,short age){
  cout << "1.foo" << "\n";
}
void foo(int inum,double dnum){
  cout << "2.foo" << "\n";
}
}
namespace ns2{
void foo(char const *cname,short sage){
  cout << "3.foo" << "\n";
}
void foo(double dnum,int inum){
  cout << "4.foo" << "\n";
}
}

int main (){
  using namespace ns1;/*ns1中的foo函数在当前作用域内可见*/
  using ns2::foo;/*ns2中的foo函数引入到当前作用域(相当于定义)*/
  /*ns2中的foo函数在此作用域下将ns1中的foo函数隐藏,只会匹配ns2中的foo,不会去ns1中寻找*/
  char* name = nullptr;
  short age = 20;
  foo(name,age);
  char dou = 'a';
  int var = 20;
  foo(var,dou);
  return 0;
}
