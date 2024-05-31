// 输出输入操作符重载
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

class human {
public:
  human(const int f_age = 0, const string f_name = "")
      : m_age(f_age), m_name(f_name) {}

private:
  int m_age;
  string m_name;
  friend ostream &operator<<(ostream &os, const human &that);
  friend istream &operator>>(istream &os, human &that);
};

ostream &operator<<(ostream &os, const human &that) {
  os << that.m_name << ": "
     << "m_age is " << that.m_age;
  return os;
}
istream &operator>>(istream &is, human &that) {
  is >> that.m_name >> that.m_age;
  return is;
}
int main() {
  human h1(10, "wangshuai"), h2(20, "huamengjun");
  cout << h1 << endl << h2 << endl;
  cin >> h1;
  cout << h1;
}
