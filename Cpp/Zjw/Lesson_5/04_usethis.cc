// 常对象和常函数
#include <cstring>
#include <iostream>

using namespace std;

class human {
public:
  // 定义一个非常函数
  void set_attribute(int m_age) { 
    this->get_attribute();
    cout << "非常函数" << endl; 
    this->m_age = m_age;
  }
  // 定义一个常函数
  void get_attribute() const { 
    // const_cast<human*>(this)->m_age = 200; 
    // m_age = 300;
    // cout << "(mutable)m_age of h2 = " << m_age << endl;
    cout << "常函数" << endl; 

  }
  //定义一个非常函数
  // void get_attribute() {
  //
  //   cout << "非常函数" << endl;
  // }

private:
 mutable int m_age;
  char m_name[64];
};
int main() {
  // 定义一个非常对象
  human h1;
  //调用常函数,将重载的函数去掉,不然匹配优先级会导致调用非常函数
  h1.get_attribute();
  // 定义一个常对象
  const human h2 = h1;
  //调用一个常函数
  h2.get_attribute();
  //不可调用非常函数
  // h2.set_attribute(10);
}
