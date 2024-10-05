// 比较类双目操作符
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class human {
public:
  human(const int f_age = 0, const string f_name = "")
      : m_age(f_age), m_name(f_name) {}

  void getinfo() const {
    cout << "m_age is " << m_age << endl;
    cout << "m_name is " << m_name << endl;
  }
  bool operator==(const human &that) const {
    return this->m_age == that.m_age && this->m_name == that.m_name;
  }

private:
  int m_age;
  string m_name;
};

bool operator!=(const human &L, const human &R) { return !(L == R); }

int main() {
  human h1(45, "刘备"), h2(41, "张飞"), h3(42, "关羽");
  cout << "h2 == h1 is " << (h2 == h1) << endl;
  cout << "h3 != h2 is " << (h3 != h2) << endl;
}
