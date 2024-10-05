// 必须定义一个无参(带有缺省参数)构造函数
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class A {
public:
  A(int i) { m_i = i; }

private:
  int m_i;
};
class human {
public:
  human() {
    /*int m_age;*/
    /*string m_name;*/
    /*A a;*/ /*调用无参构造函数,但是没定义*/
    cout << "我是自定义的构造函数" << endl;
  }

private:
  int m_age;
  string m_name;
  A a;
};

int main() { human h1; }
