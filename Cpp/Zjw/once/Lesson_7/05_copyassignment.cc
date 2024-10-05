// 拷贝赋值函数
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class human {
public:
  human(int f_age = 0, string f_name = "") : m_age(f_age), m_name(f_name) {
    cout << "我是带有缺省参数的构造函数!" << endl;
  }
  human(const human &that) : m_age(that.m_age), m_name(that.m_name) {
    cout << "我是自定义的拷贝构造函数!" << endl;
  }
  human &operator=(const human &that) {
    cout << "我是自定义的拷贝赋值函数!" << endl;
    this->m_age = that.m_age;
    this->m_name = that.m_name;
    return *this;
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
  human h1(24, "wangshuai");
  human h2;
  h2 = h1;
  h2.getinfo();
}
