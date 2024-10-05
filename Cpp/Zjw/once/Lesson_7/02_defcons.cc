// 默认构造函数
#include <iostream>
using std::cout;
using std::endl;
using std::string;

class human {
public:
  human() { cout << "我是自定义的无参构造函数" << endl; }

private:
  int m_age;
  string m_name;
};

int main() { human h1; }
