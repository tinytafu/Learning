// 必须显示初始化
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class human {
public:
  human(string f_name) : m_name(f_name), m_len(f_name.size()) {}
  void getinfo() {
    cout << "m_name is " << m_name << endl;
    cout << "m_len is " << m_len << endl;
  }

private:
  int m_len;
  string m_name;
};

int main() {

  human h1("wangshuai");
  h1.getinfo();
}
