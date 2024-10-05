// 类型推导 不是 类型照抄
#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;
int main() {
  int a = 10;
  const int b = 20;

  auto c = a; // c的类型就是int
  // 利用typeid计算一下c的类型os:i
  cout << "type of c is " << typeid(c).name() << endl;
  // 计算一下c和a的地址是否一样,看看是不是按照引用推导ok:c和a的地址不同,c不是一个引用
  cout << "&c is " << &c << ",&a is " << &a << endl;
  // 看看推导后的c是否可以被修改,卡看是不是推导出const
  c++; // ok:支持修改,c不被const修饰
  //---------------------------------------------------

  auto d = b; // d的类型就是int,不会推导出const
  // 利用typeid计算一下d的类型ok:i
  cout << "type of d is " << typeid(d).name() << endl;
  // 计算一下d和b的地址是否一样,看看是不是按照引用推导ok:d和b的地址不同,d不是一个引用
  cout << "d is " << &d << ",&b is " << &b << endl;
  // 看看推导后的d是否可以被修改,卡看是不是推导出const
  d++; // ok:支持修改,d不被const修饰
  //---------------------------------------------------

  const auto e = b; // e的类型就是const int
  // 利用typeid计算一下e的类型ok:i
  cout << "type of e is " << typeid(e).name() << endl;
  // 计算一下e和b的地址是否一样,看看是不是按照引用推导ok:e和b的地址不同,e不是一个引用
  cout << "d is " << &d << ",&b is " << &b << endl;
  // 看看推导后的e是否可以被修改,看看是不是推导出const
  // e++; // error:支持修改,e被const修饰
  //---------------------------------------------------

  // 第一种自动推导出const的情况:当类型是const type*的时候
  // ptr的类型是PKc P是pointer,K是const,c是char
  auto ptr = "wangshuai"; //"wangshuai" == 'w'的地址且是可读的:const char*
  // 利用typeid计算一下ptr的类型是什么
  cout << "type of ptr is " << typeid(ptr).name() << endl;
  // 看看ptr所指向的对象是否可修改
  // *ptr = 'a';//error:ptr指向的对象不可更改
}
