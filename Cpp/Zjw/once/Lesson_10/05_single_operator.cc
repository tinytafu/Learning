// 运算符单目操作符重载
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
class human {
public:
  human(const int f_age = 0) : m_age(f_age) {}

  human operator-() const { return human(-this->m_age); }

private:
  int m_age;
  friend ostream &operator<<(ostream &os, const human &R);
  friend human operator!(const human &R);
};

// 输出操作符重载函数 -- 输出自定类型的对象
ostream &operator<<(ostream &os, const human &R) {
  os << "m_age is " << R.m_age;
  return os;
}
//! 单目操作符重载函数
human operator!(const human &R) { return human(!(R.m_age)); }

int main() {
  human h1(20);
  cout << h1 << endl;
  human ret_h1 = -h1;
  cout << ret_h1 << endl;
  cout << "---------" << endl;
  human h2(30);
  human ret_h2 = !h2;
  cout << ret_h2 << endl;
}
