// 赋值类双目操作符
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class human {
public:
  human(int f_age = 0, string f_name = "") : m_age(f_age), m_name(f_name) {}
  void getinfo() const {
    cout << "m_age is " << m_age << endl;
    cout << "m_name is " << m_name << endl;
  }
  human &operator+=(const human &that) {
    this->m_age = this->m_age + that.m_age;
    this->m_name = this->m_name + "+" + that.m_name;
    return *this;
  }

private:
  int m_age;
  string m_name;
  friend human &operator-=(human &L, const human &R);
};

human &operator-=(human &L, const human &R) {
  L.m_age = L.m_age - R.m_age;
  L.m_name = L.m_name + "-" + R.m_name;
  return L;
}

int main() {
  human h1(10, "wangshuai"), h2(20, "huamengjun"), h3(30, "wangmi");
  h1 += h2;
  h1.getinfo();
  h3 -= h2;
  h3.getinfo();
}
