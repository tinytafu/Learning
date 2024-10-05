// 运算符自增自减++ --操作符重载
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;
using std::string;

class human {
public:
  human(const int f_age = 0) : m_age(f_age) {}
  // 前++ 前--
  human &operator++() {
    this->m_age += 1;
    return *this;
  }
  human &operator--() {
    this->m_age -= 1;
    return *this;
  }
  // 后++ 后--
  human operator++(int) {
    human old = *this;
    this->m_age += 1;
    return old;
  }
  human operator--(int) {
    human old = *this;
    this->m_age -= 1;
    return old;
  }

private:
  int m_age;
  friend ostream &operator<<(ostream &os, const human &R);
  friend human operator-(human &that, const int &L);
  friend human operator+(human &that, const int &L);
};

// 减法操作符重载函数
human operator-(human &that, const int &R) { return human(that.m_age - 1); }
// 加法操作符重载函数
human operator+(human &that, const int &R) { return human(that.m_age + 1); }

// 输出操作符重载函数 -- 输出自定类型的对象
ostream &operator<<(ostream &os, const human &R) {
  os << "m_age is " << R.m_age;
  return os;
}
int main() {
  human h1(10), h2(20);

  cout << "h1++ is " << h1++ << endl;
  cout << "++h1 is " << ++h1 << endl;
  cout << "h1-- is " << h1-- << endl;
  cout << "--h1 is " << --h1 << endl;

  cout << "h2++ is " << h2++ << endl;
  cout << "++h2 is " << ++h2 << endl;
  cout << "h2-- is " << h2-- << endl;
  cout << "--h2 is " << --h2 << endl;
}
