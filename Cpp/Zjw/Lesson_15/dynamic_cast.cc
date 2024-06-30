// 动态类型转换
#include <iostream>
using std::cout;
using std::endl;

class human {
public:
  virtual void foo() {
  } // 生成一个虚函数表 -- 存储human类的各种的信息和虚函数的地址信息&human::foo
};

class man : public human {
}; // 生成一个虚函数表 -- 存储man类的各种信息和虚函数的地址信息&human::foo
class child : public man {
}; // 生成一个虚函数表 -- 存储child类的各种信息和虚函数的地址信息&human::foo
class person {};
int main() {
  human h1;
  man m1;
  child ch;
  person p1;
  // 指向子类类型的指针类型可以隐式转换为指向基类类型的指针类型
  human *ph1 = &m1;
  human *ph2 = &ch;
  // 指向基类类型的指针类型需要使用静态
  /*先检查man*的类型是不是可以隐式转换为human*,若可以,就转换
    转换转换为指向子类类型的指针类型*/
  // man *pm1 = static_cast<man *>(ph1);
  /*先检查child*的类型是不是可以隐式转换为human*,若可以,就转换
    转换转换为指向子类类型的指针类型*/
  /* child *pch = static_cast<child *>(ph2);
  child *pcm1 = static_cast<child *>(&m1);
  child *pch1 = static_cast<child *>(&h1); */

  /*----------dynamic_cast----------*/
  // 根据ph1找到指向对象的内存空间,拿到内存空间中的虚函数表指针,找到虚函数表,找到类的相关信息与man*
  // 比较,若相同则转换成功,不相同返回NULL,运行时转换的
  man *pm1 = dynamic_cast<man *>(ph1);
  cout << "pm1: " << pm1 << endl;
  child *pch = dynamic_cast<child *>(ph2);
  cout << "pch: " << pch << endl;
  person *pp1 = dynamic_cast<person *>(ph2);
  cout << "pp1: " << pp1 << endl;
}
