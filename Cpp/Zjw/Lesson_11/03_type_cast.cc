// 类型转换操作符

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

// 前向声明
class human;
class person {
public:
  person() : m_age(0) {}
  // 类型转换构造函数
  person(const human &that);
  operator human() const;

private:
  int m_age;
  friend ostream &operator<<(ostream &os, const person &that);
};

class human {
public:
  human() : m_age(0) {}
  // 源类型为整数类型的类型转换构造函数
  human(const int f_age) : m_age(f_age) {
    cout << "human类中的类型转换构造函数" << endl;
  }
  int get_m_age() const { return m_age; }
  // 类型转换操作符函数
  operator int() const { return this->m_age; }

private:
  int m_age;
  friend ostream &operator<<(ostream &os, const human &that);
};

ostream &operator<<(ostream &os, const human &that) {
  os << "m_age is " << that.m_age;
  return os;
}
ostream &operator<<(ostream &os, const person &that) {
  os << "m_age is " << that.m_age;
  return os;
}
person::person(const human &that) : m_age(that.get_m_age()) {}
person::operator human() const { return human(); }
int main() {
  // 基本类型到类类型
  human h1 =
      10; // 直接初始化优化,h1直接调用类型转换构造函数进行定义对象中的数据
  cout << h1 << endl;
  // 类类型到基本类型
  int num = 0;
  cout << "num is " << num << endl;
  num = h1;
  // human类类型到person类型
  person p1 = h1;
  cout << p1 << endl;
  // person类型到human类型
  human h2 = p1;
  cout << h2 << endl;
}
