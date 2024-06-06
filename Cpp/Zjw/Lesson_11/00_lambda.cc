// 小括号操作符
#include <iostream>
using std::cout;
using std::endl;

class human {
public:
  human(const int f_x = 0, const int f_y = 0) : m_x(f_x), m_y(f_y) {}
  int operator()(const int f_x, const int f_y) const { return f_x + f_y; }

private:
  int m_x;
  int m_y;
};

int main() {
  human h1;
  cout << h1(1, 2) << endl;
}
