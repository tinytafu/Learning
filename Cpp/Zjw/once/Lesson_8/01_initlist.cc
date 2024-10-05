// 初始化列表
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class human {
public:
  human(int f_age = 0, string f_name = "") : m_age(f_age), m_name(f_name) {}
  human(const human &that) : m_age(that.m_age), m_name(that.m_name) {}
  human &operator=(const human &that) {
    m_age = that.m_age;
    m_name = that.m_name;
    return *this;
  }
  void getinfo() {
    cout << "m_age is " << m_age << endl;
    cout << "m_name is " << m_name << endl;
  }

private:
  int m_age;
  string m_name;
};
int main() {
  cout << "-----h1-----" << endl;
  human h1;
  h1.getinfo();
  cout << "-----h2-----" << endl;
  human h2(10, "wangshuai");
  h2.getinfo();
  cout << "-----h3-----" << endl;
  human h3 = h2;
  h3.getinfo();
  cout << "-----h4-----" << endl;
  human h4 = 10;
  h4.getinfo();
  cout << "-----h5-----" << endl;
  human h5;
  h5 = 10;
  h5.getinfo();
  cout << "-----h6-----" << endl;
  human h6;
  h6 = h5;
  h6.getinfo();
}
