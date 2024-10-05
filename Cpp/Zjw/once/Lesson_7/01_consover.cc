#include <iostream>
using namespace std;

class human {
public:
  // 无参构造函数
  /* human() {
    cout << "1.无参构造函数" << endl;
    this->m_age = 10;
    this->m_name = "wangshuai";
  } */
  // 单个参数构造函数
  /* human(int age) {
    cout << "2.单个参数的构造函数" << endl;
    this->m_age = age;
    this->m_name = "wangshuai";
  } */
  // 多个参数构造函数
  /* human(int age, string name) {
    cout << "3.多个参数的构造函数" << endl;
    this->m_age = age;
    this->m_name = name;
  } */
  human(int f_age = 10, string f_name = "wangshuai") {
    cout << "3.带有缺省参数的构造函数" << endl;
    this->m_age = f_age;
    this->m_name = f_name;
  }
  void getinfo() const {
    cout << "m_age is " << m_age << endl;
    cout << "m_name is " << m_name << endl;
  }

private:
  int m_age;
  string m_name;
};

int main() {
  // 1.利用无参构造函数定义对象
  human h1;
  h1.getinfo();
  // 2.利用单个参数构造函数定义对象
  human h2(20);
  h2.getinfo();
  // 3.利用多个参数的构造函数定义对象
  human h3(30, "huamengjun");
  h3.getinfo();
}
